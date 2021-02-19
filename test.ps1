param (
    [Parameter(Mandatory = $true)]
    [string] $ID,
    [string] $SourceFolder = "./bin"
)

$files = Get-ChildItem "./data" -Filter *.in

foreach ($input in $files) {
    $content = Get-Content $input
    $base = $input.BaseName
    $time = (Measure-Command {$content | & $SourceFolder/$ID > "./data/$base.out"}).TotalSeconds
    $output = Get-Content "./data/$base.out"
    $answer = Get-Content "./data/$base.ans"

    Write-Host -NoNewline "$($input.Name)"
    $ok = $True
    
    if ($answer.Count -eq 1) { # answer has one line
        $answer = @($answer)
    }
    if ($output.Count -eq 1) { # output has one line
        $output = @($output)
    }

    for ($i = 0; $i -le ([Math]::Min($answer.Count, $output.Count) - 1); $i++) {
        if ($output[$i].TrimEnd() -ne $answer[$i].TrimEnd()) {
            if ($ok) {
                $ok = $False
                Write-Host " `u{274C}      $time s" # ❌
            }
            Write-Host "$($i + 1) | $($output[$i]) <=> $($answer[$i])"
        }
    }
    if ($answer.Count -gt $output.Count) {
        if ($ok) {
            $ok = $False
            Write-Host " `u{274C}      $time s" # ❌
        }
        foreach ($i in $output.Count..($answer.Count - 1)) {
            Write-Host "$($i + 1) | <=> $($answer[$i])"
        }
    }
    elseif ($answer.Count -lt $output.Count) {
        if ($ok) {
            $ok = $False
            Write-Host " `u{274C}      $time s" # ❌
        }
        foreach ($i in $answer.Count..($output.Count - 1)) {
            Write-Host "$($i + 1) | $($output[$i]) <=>"
        }
    }

    if ($ok) {
        Write-Host " `u{2714}       $time s" # ✔
    }
    else {
        Write-Host ""
    }
}
