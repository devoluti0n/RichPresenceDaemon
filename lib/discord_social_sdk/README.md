Get the discord_social_sdk from discord develloper stuff

Also if using with Qt you can to convert the .lib into a .dll.a because Qt using MinGW and not MSVC.

```
gendef discord_partner_sdk.dll 
dlltool --dllname discord_partner_sdk.dll --def  discord_partner_sdk.def --output-lib discord_partner_sdk.dll.a
```