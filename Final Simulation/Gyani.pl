#!/usr/bin/perl
use Scalar::Util qw(looks_like_number);
use utf8;
use Unicode::Normalize;

#--------------------------------------------------------x--------------------------------------------------------#
#The following code snippet parses through the graphml file and stores valid universities in a vector for future comparisons.
my $substr = "<data key=\"d10\">";
my $substr2 = "</data>";
my $ft = "";
my $lines;
my @UNIV;
my $fi = @ARGV[0];
my $sem=semget(111, 1, &IPC_CREAT | 0666) || die "semget: $!\n";

sub IPC_RMID    {10};
sub IPC_CREAT   {0001000};
sub semacq {
    my $sem=shift;
    semop($sem, pack("s3", 0, -1, 0)) || die "semw: $!\n";
}

sub semrel {
    my $sem=shift;
    semop($sem, pack("s3", 0, +1, 0)) || die "sems: $!\n";
}

open(my $file, '<', $fi);
do
{
    $lines = <$file>; # reading lines one by one
    if (index($lines, $substr) != -1)
    {
        $ft = substr($lines,index($lines, $substr)+(length $substr),index($lines, $substr2)-(index($lines, $substr)+(length $substr))),"\n";
        my %params = map { $_ => 1 } @UNIV;
        if(! exists($params{$ft}))
        {
            push @UNIV, $ft; #storing in the vector
        }
    }
}while($lines);
close($file);
foreach (@UNIV)
{
    $_ = uc($_);
}
print "***************************************GYANI***************************************\n";
print  "Available Universities :: ","@UNIV","\n";
#--------------------------------------------------------x--------------------------------------------------------#
#Actual Query handling starts.
open(FILE1,'>',"query.txt");
$lines = "DONE";
print FILE1 $lines;
close(FILE1);
my $tryagain = 1;
my $scalarpid=fork();		# forking to create two processes.
if($scalarpid == 0) 		# child process
{
	my $arg = @ARGV[0];
	exec("./analyser $arg");	# calling analyser.
	exit 0;
}
else{    			#parent process
	sleep(1);
	my $released = 1;	
	while($tryagain == 1)	#main loop
	{
		if($released == 1)
		{
			semacq($sem);
			$released = 0;
		}
    my $error = 0;
    print "Enter Your Query :: ";
    my $choice = 0;
    my @words;
    while ($choice == 0)
    {
        my $query = <STDIN>; #input query
        chomp $query;
        my $result = NFD($query);
        $result !~ s/[^[:ascii:]]//g; # Remove all non-ascii.
        $result =~ s/ - / /g; # Replace all " - " with " "
        $result =~ s/[^A-Za-z0-9]/ /g; # Replace all non-alphanumericals with " "
        $query = $result;
        $query = uc($query);
        @words = split / /, $query;
        my %wordmap = map { $_ => 1 } @words;
	#words to be matched
        $qt1 = "CLIQUE";
        $qt2_a = "IMPORTANCE";
        $qt2_b = "IMPORTANT";
        $qt2_1 = "FRIENDS";
        $qt2_2 = "FRIEND";
        $qt2_3 = "NUMBER";
        $qt2_4 = "ALL-PAIR";
        $qt3 = "SHORTEST";
        $qt3_1 = "LENGTH";
        $qt3_2 = "PATH";
        $qt3_3 = "DISTANCE";
        $qt3_4 = "LIST";
        $qt3_5 = "PEOPLE";
        $qt3_6 = "PERSON";
        $qt3_7 = "NAME";
        $qt3_8 = "ID";
        $qt3_9 = "ALL";
        $qt3_10 = "PAIRS";
        $qt3_11 = "PATHS";
        $qt3_12 = "PERSONS";
        $num_id = 0;
        if(exists($wordmap{$qt1})) #query 1
        {
            $choice = 1;
        }
        elsif(exists($wordmap{$qt2_a})||exists($wordmap{$qt2_b}))  #query 5 and 6
        {
	    if(exists($wordmap{$qt2_1})||exists($wordmap{$qt2_2}))
            {
                $choice = 6;
            }
            else
            {
                $choice = 5;
            }
        }
        elsif(exists($wordmap{$qt3}))
        {
            my $size = @words;
            my $number = 0;
            my $uni_number = 0;
            foreach (@words)
            {
                if (looks_like_number($_))
                {
                    $number ++;
                }
                my %unis = map { $_ => 1 } @UNIV;
                if(exists($unis{$_}))
                {
                    $uni_number ++;
                }
            }
            if($number > 1 && $uni_number > 1)
            {
                if( ( exists($wordmap{$qt3_1})||exists($wordmap{$qt3_1}) && exists($wordmap{$qt3_2} ) || exists($wordmap{$qt3_3}) ))
                {
                    $choice = 2;
                }
                elsif( exists($wordmap{$qt3_2})||exists($wordmap{$qt3_11})||exists($wordmap{$qt3_4})||exists($wordmap{$qt3_5})||exists($wordmap{$qt3_6})||exists($wordmap{$qt3_12})||exists($wordmap{$qt3_7})||exists($wordmap{$qt3_8})||exists($wordmap{$qt3_9}) )
                {
                    $choice = 3;
                }
            }
            elsif(($number == 1 && $uni_number >= 1)||($uni_number == 1 && $number >= 1))
            {
                if( ( exists($wordmap{$qt3_9})||exists($wordmap{$qt3_10})||exists($wordmap{$qt3_11}) || exists($wordmap{$qt2_3} ) ))
                {
                    if(exists($wordmap{$qt2_1})||exists($wordmap{$qt2_2}))
                    {
                        $choice = 6;
                    }
                    else
                    {
                        $choice = 5;
                    }
                }
                else
                {
                    $choice = 2;
                }
            }
            else
            {
                $choice = 4;
            }
        }
        elsif(exists($wordmap{"EXIT"})||exists($wordmap{"CLOSE"})||exists($wordmap{"QUIT"}))
        {
            $choice = 7;
        }
        my $size = @words;
        if($choice != 0)
        {
        }
        else
        {
            print "\nSorry, Could Not Match The Query.\nPlease Re-Enter Your Query :: ";
        }
    }
    if($choice == 7) # for exiting Gyani
    {
		open(FILE,'>',"query.txt");
        $lines = "-1\n-1\n-1\n-1\n-1\n";
        print FILE $lines;
        close(FILE);
		semrel($sem);
        exit;
    }
# After getting the choice, now we look for other details like id and university.
    my @given =  (  " 1. Size of Clique of a given person (identified by university name and ID)                                                    REQUIREMENT     ::  1 UNIV, 1 ID",
                    " 2. The length of the shortest path between two given people                                                                   REQUIREMENT     ::  2 UNIV, 2 ID",
                    " 3. The list of people on the shortest path between two given people                                                           REQUIREMENT     ::  2 UNIV, 2 ID",
                    " 4. The shortest path in the graph (between any pair of people)                                                                REQUIREMENT     ::  0 UNIV, 0 ID",
                    " 5. The importance of the given person (the importance is the number of the all-pair shortest paths that include that person)  REQUIREMENT     ::  1 UNIV, 1 ID",
                    " 6. Is any of the friends of a given person more important that him/her                                                        REQUIREMENT     ::  1 UNIV, 1 ID");
    my $id1 = -1;
    my $id2 = -1;
    my $uni1 = -1;
    my $uni2 = -1;
    if($choice == 4)
    {
    }
    elsif( ($choice == 1)||($choice == 5)||($choice == 6) )
    {
        my $number_id = 0;
        my $number_uni = 0;
        my $id = -1;
        my $uni = -1;
        foreach (@words)
        {
            if (looks_like_number($_))
            {
                $number_id ++;
            if($number_id == 1)
                {
                    $id = $_;
                }
            }
            my %unis = map { $_ => 1 } @UNIV;
            if(exists($unis{$_}))
            {
                $number_uni ++;
                if($number_uni == 1)
                {
                    $uni = $_;
                }
            }
        }
        if($number_id < 1||$number_uni < 1)
        {
            $id1 = $id;
            $uni1 = $uni;
            $error = 1;
        }
        else
        {
            $id1 = $id;
            $uni1 = $uni;
        }
    }
    elsif( ($choice == 2)||($choice == 3) )
    {
        my $number_id = 0;
        my $number_uni = 0;
        my $id_a = -1;
        my $id_b = -1;
        my $uni_a = -1;
        my $uni_b = -1;
        foreach (@words)
        {
            if (looks_like_number($_))
            {
                $number_id ++;
                if($number_id == 1)
                {
                    $id_a = $_;
                }
                if($number_id == 2)
                {
                    $id_b = $_;
                }
            }
            my %unis = map { $_ => 1 } @UNIV;
            if(exists($unis{$_}))
            {
                $number_uni ++;
                if($number_uni == 1)
                {
                    $uni_a = $_;
                }
                elsif($number_uni == 2)
                {
                    $uni_b = $_;
                }
            }
        }
        if($number_id < 2||$number_uni < 2)
        {
            $id1 = $id_a;
            $id2 = $id_b;
            $uni1 = $uni_a;
            $uni2 = $uni_b;
            $error = 1;
        }
        else
        {
            $id1 = $id_a;
            $id2 = $id_b;
            $uni1 = $uni_a;
            $uni2 = $uni_b;
        }
    }
    if($error == 1)
    {
        print "#---------------------------INTERPRETED QUERY---------------------------#\n";
        print " QUERY :: ",@given[$choice-1],"\n";
        print " \nPERSON 1    =>\n";
        if($uni1 == -1)
        {
            print " UNIVERSITY  :: NOT GIVEN\n";
        }
        else
        {
            print " UNIVERSITY  :: ",$uni1,"\n";
        }
        if($id1 == -1)
        {
            print " ID          :: NOT GIVEN\n";
        }
        else
        {
            print " ID          :: ",$id1,"\n";
        }
        print " \nPERSON 2    =>\n";
        if($uni2 == -1)
        {
            print " UNIVERSITY  :: NOT GIVEN\n";
        }
        else
        {
            print " UNIVERSITY  :: ",$uni2,"\n";
        }
        if($id2 == -1)
        {
            print " ID          :: NOT GIVEN\n";
        }
        else
        {
            print " ID          :: ",$id2,"\n";
        }
        print "#-----------------------------------x-----------------------------------#\n";
        print "ERROR,TRY AGAIN \n";
        $tryagain = 1;
    }
    else
    {
        print "#---------------------------INTERPRETED QUERY---------------------------#\n";
        print " QUERY :: ",@given[$choice-1],"\n";
        print " \nPERSON 1    =>\n";
        if( ($uni1 == -1)||($id1 == -1) )
        {
            print " UNIVERSITY  :: NOT REQUIRED\n";
            print " ID          :: NOT REQUIRED\n";
        }
        else
        {
            print " UNIVERSITY  :: ",$uni1,"\n";
            print " ID          :: ",$id1,"\n";
        }
        print " \nPERSON 2    =>\n";
        if( ($uni2 == -1)||($id2 == -1) )
        {
            print " UNIVERSITY  :: NOT REQUIRED\n";
            print " ID          :: NOT REQUIRED\n";
        }
        else
        {
            print " UNIVERSITY  :: ",$uni2,"\n";
            print " ID          :: ",$id2,"\n";
        }
        print "#-----------------------------------x-----------------------------------#\n";
        my $question_again = 1;
        while($question_again == 1)
        {
            print "DO YOU WANT TO ANALYZE THIS INTERPRETED QUERY (Y/N) ?\n";
            chomp ($loop);
            
            my $loop = <STDIN>;
            $loop = uc(substr ($loop,0,1));
            if($loop eq "Y")
            {
                $tryagain = 0;
                $question_again = 0;
            }
            elsif($loop eq "N")
            {
                $tryagain = 1;
                $question_again = 0;
            }
            else
            {
                print "WRONG INPUT\n";
                $question_again = 1;
            }
        }
        if($tryagain == 0)#analyzer
        {
            print "#---------------------------------------ANALYZER---------------------------------------#\n";
            $tryagain = 1;
            
            open(FILE,'>',"query.txt");
            $lines = "$choice\n$id1\n$uni1\n$id2\n$uni2\n";
            print FILE $lines;
            close(FILE);
            $released = 1;
            semrel($sem);
            sleep(2);
            print "#-------------------------------------------x------------------------------------------#\n";
        
        }
    }
}
}
