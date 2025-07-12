# {
#     "version": 1.0,

#     "track": "Demons are a girl best friend",
#     "artist": "Powerwolf",
#     "album": "Sacrement Of Sin",
#     "duration": 240,
    
#     "year" : 2008



# }

# Install-Module WebSocket -Scope CurrentUser -Force
Import-Module WebSocket -Force



$ws = Get-WebSocket -SocketUrl "ws://localhost:32322"

$msg = @{
    "version" = "1.0"
    "music" = @{
        "track" = "Demons are a girl best friend"
        "artist"= "Powerwolf"
        "album" = "Sacrement Of Sin"
        "duration" = 240
    }


}
$json = $msg | ConvertTo-Json

echo $json

$bytes = [System.Text.Encoding]::UTF8.GetBytes($json)

$ws.Send($bytes)