<#
.Synopsis
Runs and times the source code with specified input.
.Parameter ID
Name of program to run.
.Parameter SourceFolder
Name of folder in which the program resides.
.Parameter InputFile
Name of the file to read input from.
.Parameter OutFile
Name of the file to write output to.
.Example
run 101
Run program 101.exe in ./bin with input from in.txt and output to out.txt.
#>
param (
    [Parameter(Mandatory = $true)]
    [string] $ID,
    [string] $SourceFolder = "./bin",
    [string] $InputFile = "in.txt",
    [string] $OutFile = "out.txt"
)
$time = (Measure-Command {Get-Content $InputFile | & $SourceFolder/$ID > $OutFile}).TotalSeconds
Write-Output "Run time: $time seconds"