set ns [new Simulator]

set tf [open out.tr w]
$ns trace-all $tf
set nf [open out.nam w]
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns color 1 "red" 
$ns color 2 "blue"

$ns duplex-link $n0 $n2 2Mb 1ms DropTail
$ns duplex-link $n1 $n2 2Mb 1ms DropTail
$ns duplex-link $n2 $n3 2Mb 1ms DropTail

set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $tcp1

set TCPS0 [new Agent/TCPSink]
set TCPS1 [new Agent/TCPSink]
$ns attach-agent $n3 $TCPS0
$ns attach-agent $n3 $TCPS1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set tel1 [new Application/Telnet]
$tel1 attach-agent $tcp1

$tel1 set packetSize_ 500Mb
$tel1 set interval_ 0.001

$tcp0 set class_ 1 
$tcp1 set class_ 2

$ns connect $tcp0 $TCPS0
$ns connect $tcp1 $TCPS1

proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $tf
	close $nf

	set time 2
	set fCount 0
	set tCount 0
	set tf [open out.tr r]
	while {[gets $tf line] != -1} {
		if { [string match "*tcp*0.0*3.0*" $line] } {
			set fCount [expr $fCount + 1]
		}
		if { [string match "*tcp*1.0*3.1*" $line] } {
			set tCount [expr $tCount + 1]
		}
	}
	puts "Throughput of FTP: [expr $fCount/$time]"
	puts "Throughput of TELNET: [expr $tCount/$time]"
	exit 0
}

$ns at 0.01 "$ftp0 start"
$ns at 0.01 "$tel1 start"
$ns at 2.01 "finish"
$ns run
