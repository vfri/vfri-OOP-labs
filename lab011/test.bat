@echo off

set PROGRAM="%~1"

echo %PROGRAM%
echo %TEMP%


REM запуск программы без параметров
%PROGRAM%
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с одним параметром
%PROGRAM% theOnlyParameter
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами 
%PROGRAM% houseJackShort.txt cat dog 
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем несуществующего файла
%PROGRAM% notExistingFile anyString > "%TEMP%\outputNotExists.txt"
IF NOT ERRORLEVEL 1 GOTO err
fc.exe "%TEMP%\outputNotExists.txt" testcases\notExistingFileResult.txt
IF ERRORLEVEL 1 GOTO err

echo "not exist"

echo.

REM запуск программы с именем существующего файла и с отсутствующим образцом
%PROGRAM% houseJackShort.txt hgfedcba > "%TEMP%\outputAbsent.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC /B "%TEMP%\outputAbsent.txt" houseShortAbsentResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% houseJackShort.txt dog > "%TEMP%\outputDog.txt""
IF ERRORLEVEL 1 GOTO err
FC /B "%TEMP%\outputDog.txt" houseShortDogResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% houseJackShort.txt rat > "%TEMP%\outputRat.txt""
IF ERRORLEVEL 1 GOTO err
FC /B "%TEMP%\outputRat.txt" houseShortRatResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% houseJackShort.txt at > "%TEMP%\outputAt.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "%TEMP%\outputAt.txt" houseShortAtResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% houseJackFull.txt Ja > "%TEMP%\outputJaFull.txt"
IF ERRORLEVEL 1 GOTO err
FC /B "%TEMP%\outputJaFull.txt" houseJackFullJaResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT
