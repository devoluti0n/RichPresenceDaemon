


To generate .dll.a (that works with MingW that Qt uses)
```
gendef discord_partner_sdk.dll
dlltool -d discord_partner_sdk.def -l discord_partner_sdk.dll.a -k -D discord_partner_sdk.dll
```