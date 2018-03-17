@echo off

lab011.exe houseJackShort.txt house > result0.txt

REM запуск программы без параметров
lab011.exe
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с одним параметром
lab011.exe theOnlyParameter
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами 
lab011.exe houseJackShort.txt cat dog 
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем несуществующего файла
lab011.exe notExistingFile anyString > outputNotExists.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B outputNotExists.txt notExistingFileResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с отсутствующим образцом
lab011.exe houseJackShort.txt hgfedcba > outputAbsent.txt
IF NOT ERRORLEVEL 1 GOTO err
FC /B outputAbsent.txt houseShortAbsentResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
lab011.exe houseJackShort.txt dog > outputDog.txt
IF ERRORLEVEL 1 GOTO err
FC /B outputDog.txt houseShortDogResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
lab011.exe houseJackShort.txt rat > outputRat.txt
IF ERRORLEVEL 1 GOTO err
FC /B outputRat.txt houseShortRatResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
lab011.exe houseJackShort.txt at > outputAt.txt
IF ERRORLEVEL 1 GOTO err
FC /B outputAt.txt houseShortAtResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
lab011.exe houseJackFull.txt Ja > outputJaFull.txt
IF ERRORLEVEL 1 GOTO err
FC /B outputJaFull.txt houseJackFullJaResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
