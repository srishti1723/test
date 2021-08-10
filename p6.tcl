set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf

set nf [open out.nam w]
$ns namtrace-all-wireless $nf 500 500

set topo [new Topography]
$topo load_flatgrid 500 500

$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF

create-god 3

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$n0 set X_ 10
$n0 set Y_ 10
$n0 set Z_ 0

$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0

$n2 set X_ 400
$n2 set Y_ 400
$n2 set Z_ 0

$ns at 0.0 "$n0 setdest 10 10 15"
$ns at 0.0 "$n1 setdest 100 100 15"
$ns at 0.0 "$n2 setdest 400 400 15"

set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1

set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns attach-agent $n2 $sink2

set ftp0 [new Application/FTP]
set ftp1 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp1 attach-agent $tcp1

$ns connect $tcp0 $sink1
$ns connect $tcp1 $sink2

proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $tf
	set ctr1 0
	set ctr2 0
	set tf [open out.tr r]
	while {[gets $tf line] != -1} {

		if {[string match "r*_1_*AGT*" $line]} {
			set ctr1 [expr $ctr1 + 1]
		}
		if {[string match "r*_2_*AGT*" $line]} {
			set ctr2 [expr $ctr2 + 1]
		}
	}
	puts "\nThroughput from n0 to n1: $ctr1"
	puts "Throughput from n1 to n2: $ctr2"
	exit 0
}

$ns at 50 "$n1 setdest 300 300 15"
$ns at 100 "$n1 setdest 100 100 15"

$ns at 1 "$ftp0 start"
$ns at 1 "$ftp1 start"
$ns at 150 "finish"
$ns run
