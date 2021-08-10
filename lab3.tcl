set ns [new Simulator]

set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

puts "Enter error rate (<1) : "
gets stdin erate

puts "Enter data rate (in Mbps) : "
gets stdin drate
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$n1 label "udp/source"
$n5 label "udp/null"
$n0 color "blue"
$n1 color "blue"
$n2 color "blue"
$n3 color "blue"
$n4 color "red"
$n5 color "red"
$n6 color "red"

$ns make-lan "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3

$ns make-lan "$n4 $n5 $n6" 10Mb 10ms LL Queue/DropTail Mac/802_3

$ns duplex-link $n3 $n6 10Mb 10ms DropTail

set udp1 [new Agent/UDP]
set null5 [new Agent/Null]
$ns attach-agent $n1 $udp1
$ns attach-agent $n5 $null5

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

$ns connect $udp1 $null5

set err [new ErrorModel]
$ns lossmodel $err $n3 $n6
$err set rate_ $erate

$cbr1 set packetSize_ $drate.Mb
$cbr1 set interval_ 0.001

proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $nf
	close $tf
	
	set count 0
	set tr [open out.tr r]
	while {[gets $tr line] != -1} {

		if {[string match "* 8 5 *" $line]} {
			set count [expr $count+1]
		}
	}
	set thr [expr $count/5]
	puts "Throughput : $thr"
	exit 0
}
$ns at 0.1 "$cbr1 start"
$ns at 5.1 "finish"
$ns run
