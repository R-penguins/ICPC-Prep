param (
    [Parameter(Mandatory = $true)]
    [string] $name
)

cd ./data
Remove-Item *
unzip ../$name
cd ..