module("helpers", package.seeall)

--[[
   Some useful helper functions for working with Lua types.
--]]


--[[
   Split the given string on the delimiter character into individual strings
   and return these as an array

   @param str the string to split
   @param delim the delimiter to split on
   @return An array of individual strings

--]]
function Split(str, delim)
    assert (str ~= nil)
    assert (delim ~= nil)

    local firstindex=1
    local rval = {}
    local nextindex =string.find(str, delim, firstindex, true)
    local i = 1

    while(nextindex ~= nil) do
        rval[i]=string.sub(str, firstindex, nextindex-1)
        firstindex=nextindex+1
        nextindex=string.find(str, delim, firstindex, true)
        i = i + 1
    end
    rval[i] = string.sub(str, firstindex)

    return rval
end


--[[
    Print out an array
--]]
function PrintArray(t)
    for key, value in pairs(t) do
        print(tostring(value));
    end
end


--[[
    Dump table contents to the log.
--]]
function DumpTable(t)
    local workingStr = "Dumping table..."
    if type(t) == "table" then
        for key, value in pairs(t) do
            workingStr = workingStr.."\n"..tostring(key).." = "..tostring(value)
        end
        BehaviorAPI.LogMessage(0, workingStr)
    else
        BehaviorAPI.LogError(1, workingStr.."\nError: Parameter is not a table.")
    end
end
