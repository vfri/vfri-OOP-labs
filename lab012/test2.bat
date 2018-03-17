@echo off


REM запуск программы без параметров
lab012.exe
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с одним параметром
lab012.exe theOnlyParameter
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с двумя параметрами
lab012.exe oneParameter twoParameter
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, первый не число 
lab012.exe ab 13 34ret453 > 2outputWrongSource.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputWrongSource.txt 2wrongSourceResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, первый слишком большой 
lab012.exe 37 13 34ret453 > 2outputBigSource.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputBigSource.txt 2bigSourceResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, второй меньше 2 
lab012.exe 23 1a 34ret453 > 2outputSmallDest.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputSmallDest.txt 2smallDestResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка с 
REM невалидными символами 
lab012.exe 13 17 256w3 > 2outputWrongSymb.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputWrongSymb.txt 2wrongSymbResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает слишком большое число 
lab012.exe 13 17 100000000000000 > 2outputTooBigNumber.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputTooBigNumber.txt 2tooBigNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает максимальное целое число 
lab012.exe 10 16 2147483647 > 2outputMaxIntNumber.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputMaxIntNumber.txt 2maxIntNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает минимальное целое число 
lab012.exe 10 16 -2147483648 > 2outputMinIntNumber.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputMinIntNumber.txt 2minIntNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает 0 
lab012.exe 10 16 0 > 2outputZero.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputZero.txt 2zeroResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число, на 1 больше минимального 
lab012.exe 10 16 -2147483647 > 2outputAlmostMinNumber.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputAlmostMinNumber.txt 2almostMinNumberResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2018 
lab012.exe 10 3 2018 > 2output2018To3.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2output2018To3.txt 22018To3Result.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2018 
lab012.exe 3 10 2202202 > 2output2018From3.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2output2018From3.txt 22018From3Result.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
lab012.exe 25 23 G00 > 2outputFrom25To23.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputFrom25To23.txt 2from25To23Result.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
lab012.exe 23 25 IKI > 2outputFrom23To25.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B 2outputFrom23To25.txt 2from23To25Result.txt
IF ERRORLEVEL 1 GOTO err

echo.




ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT