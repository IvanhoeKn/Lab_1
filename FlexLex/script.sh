#!/bin/bash

flex -c++ FlexAnalyzer.l
sed -i '22d' lex.yy.cc

if g++ lex.yy.cc
then
./a.out ./../Tests/test_1.txt  ./Tests/test_1/output.txt  ./Tests/test_1/statistic.txt
./a.out ./../Tests/test_2.txt  ./Tests/test_2/output.txt  ./Tests/test_2/statistic.txt
./a.out ./../Tests/test_3.txt  ./Tests/test_3/output.txt  ./Tests/test_3/statistic.txt
./a.out ./../Tests/test_4.txt  ./Tests/test_4/output.txt  ./Tests/test_4/statistic.txt
./a.out ./../Tests/test_5.txt  ./Tests/test_5/output.txt  ./Tests/test_5/statistic.txt
./a.out ./../Tests/test_6.txt  ./Tests/test_6/output.txt  ./Tests/test_6/statistic.txt
./a.out ./../Tests/test_7.txt  ./Tests/test_7/output.txt  ./Tests/test_7/statistic.txt
./a.out ./../Tests/test_8.txt  ./Tests/test_8/output.txt  ./Tests/test_8/statistic.txt
./a.out ./../Tests/test_9.txt  ./Tests/test_9/output.txt  ./Tests/test_9/statistic.txt
./a.out ./../Tests/test_10.txt ./Tests/test_10/output.txt ./Tests/test_10/statistic.txt
fi
