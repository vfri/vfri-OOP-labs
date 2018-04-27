@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM ������ ��������� ��� ����������
%PROGRAM%
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� ����������
%PROGRAM% theOnlyParameter
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������
%PROGRAM% oneParameter twoParameter
IF ERRORLEVEL 1 GOTO err

echo.


REM ������ ��������� � ����� �����������, ������ �� ����� 
%PROGRAM% ab 13 34ret453 > testcases\2outputWrongSource.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B testcases\2outputWrongSource.txt testcases\2wrongSourceResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, ������ ������� ������� 
%PROGRAM% 37 13 34ret453 > testcases\2outputBigSource.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B testcases\2outputBigSource.txt testcases\2bigSourceResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, ������ ������ 2 
%PROGRAM% 23 1a 34ret453 > testcases\2outputSmallDest.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B testcases\2outputSmallDest.txt testcases\2smallDestResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ � 
REM ����������� ��������� 
%PROGRAM% 13 17 256w3 > testcases\2outputWrongSymb.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B testcases\2outputWrongSymb.txt testcases\2wrongSymbResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ������� ������� ����� 
%PROGRAM% 13 17 100000000000000 > testcases\2outputTooBigNumber.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B testcases\2outputTooBigNumber.txt testcases\2tooBigNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ������������ ����� ����� 
%PROGRAM% 10 16 2147483647 > testcases\2outputMaxIntNumber.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputMaxIntNumber.txt testcases\2maxIntNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ����������� ����� ����� 
%PROGRAM% 10 16 -2147483648 > testcases\2outputMinIntNumber.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputMinIntNumber.txt testcases\2minIntNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� 0 
%PROGRAM% 10 16 0 > testcases\2outputZero.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputZero.txt testcases\2zeroResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� �����, �� 1 ������ ������������ 
%PROGRAM% 10 16 -2147483647 > testcases\2outputAlmostMinNumber.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputAlmostMinNumber.txt testcases\2almostMinNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ����� 2018 
%PROGRAM% 10 3 2018 > testcases\2output2018To3.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2output2018To3.txt testcases\22018To3Result.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ����� 2018 
%PROGRAM% 3 10 2202202 > testcases\2output2018From3.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2output2018From3.txt testcases\22018From3Result.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ����� 10000 � 25������ ������� � ��������� � 23����� 
%PROGRAM% 25 23 G00 > testcases\2outputFrom25To23.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputFrom25To23.txt testcases\2from25To23Result.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM ������ ��������� � ����� �����������, �������� � �������� ��������, ������ 
REM ���������� ����� 10000 � 25������ ������� � ��������� � 23����� 
%PROGRAM% 23 25 IKI > testcases\2outputFrom23To25.txt
IF ERRORLEVEL 1 GOTO err
FC /B testcases\2outputFrom23To25.txt testcases\2from23To25Result.txt
IF ERRORLEVEL 1 GOTO err

echo.

%PROGRAM% 2 16 1001001
%PROGRAM% 16 2 ffff




ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT