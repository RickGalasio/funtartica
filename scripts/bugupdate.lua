--print("START ./test/bugupdate.lua")
--print("buginc", buginc)

sprt_bug_x=sprt_bug_x+buginc
if (sprt_bug_x<0) then
   buginc=0.2
end

if (sprt_bug_x>924) then
    buginc=-0.2
end

sprt_bug_y=math.floor(math.sin(sprt_bug_x * 3.14159265/360)*150)+100

-- ######################################################
seti("sprt_bug_y",sprt_bug_y)
seti("sprt_bug_x",sprt_bug_x)

--print("END ./test/bugupdate.lua")
