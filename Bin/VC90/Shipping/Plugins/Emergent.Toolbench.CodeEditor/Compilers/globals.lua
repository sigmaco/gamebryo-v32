-- http://lua-users.org/lists/lua-l/2006-05/msg00306.html
-- Luiz Henrique de Figueiredo

-- find undefined global vars
-- typical usage: luac -p -l *.lua | lua globals.lua


local S={}
local G={}
local F

while true do
 local s=io.read()
 if s==nil then break end
 local ok,_,f=string.find(s,"^[mf].-<(.-):%d+,%d+>")
 if ok then F=f end
 local ok,_,l,op,g=string.find(s,"%[%-?(%d*)%]%s*([GS])ETGLOBAL.-;%s+(.*)$")
 if ok then
  if op=="S" then S[g]=true else G[g]=F..":"..l end
 end
end

for k,v in next,G do
 if not S[k] and not _G[k] then
  io.write(k," may be undefined in ",v,"\n")
 end
end
