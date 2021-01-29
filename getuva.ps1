<#
.Synopsis
Downloads problem statements from the UVa Online Judge
.Parameter ProblemIDs
Problem IDs to download seperated by commas
.Parameter View
Open the document after download
.Parameter Output
The output directory
.Example
get 101, 243
This command dowloads problem statements for 101 and 243 and save them in ./pdf/ .
.Example
get 101 -View
This command dowloads problem statements for 101, save it in ./pdf/ , and opens it.
.Example
get 101 -Output .
This command dowloads problem statements for 101 and save it in the current folder.
#>
param (
    [Parameter(Mandatory = $true)]
    [string[]] $ProblemIDs,
    [switch] $View,
    [switch] $Print,
    [string] $Output = "./uva-pdf"
)
if (! (Test-Path $Output)) {
    mkdir $Output
}
foreach ($id in $ProblemIDs) {
    Write-Output "Downloading $id.pdf ..."
    $problemFolder = $id.Substring(0, $id.Length - 2)
    Invoke-WebRequest "https://uva.onlinejudge.org/external/$problemFolder/$id.pdf" -OutFile "$Output/$id.pdf" -SkipCertificateCheck
    if ($View) {
        Start-Process "$Output/$id.pdf"
    }
    if ($Print) {
        Start-Process "$Output/$id.pdf" -Verb Print
    }
}