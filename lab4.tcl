set ns [new Simulator]

set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns make-lan -trace on "$n0 $n1 $n2 $n3" 100Mb 10ms LL Queue/DropTail Mac/802_3

set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set udp2 [new Agent/UDP]
set null1 [new Agent/Null]
set sink2 [new Agent/TCPSink]
set sink3 [new Agent/TCPSink]

$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1
$ns attach-agent $n2 $udp2
$ns attach-agent $n1 $null1
$ns attach-agent $n2 $sink2
$ns attach-agent $n3 $sink3

set ftp0 [new Application/FTP]
set ftp1 [new Application/FTP]
set cbr2 [new Application/Traffic/CBR]
$ftp0 attach-agent $tcp0
$ftp1 attach-agent $tcp1
$cbr2 attach-agent $udp2

$ns connect $tcp0 $sink2
$ns connect $udp2 $null1
$ns connect $tcp1 $sink3

$ftp0 set interval_ 0.001
$ftp1 set interval_ 0.001
$cbr2 set interval_ 0.01

proc finish {} {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $tf
	close $nf
	
	set count 0
	set tr [open out.tr r]
	while {[gets $tr line] !=-1 } {
		if { [string match "c*" $line] } {
			set count [expr $count + 1]
		}
	}
	puts "No of packets collided: $count"
	exit 0
}

$ns at 0.1 "$cbr2 start"
$ns at 0.1 "$ftp0 start"
$ns at 0.1 "$ftp1 start"
$ns at 5.0 "finish"
$ns run
