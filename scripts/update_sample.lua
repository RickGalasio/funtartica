--print("START ./test/update.lua")
-- ######################################################
if (sprt_mn1_x<0) then
    mn1x=math.floor(math.random() * 2)   + 1 
end
if (sprt_mn1_x>300) then
    mn1x=math.floor(math.random() * 2) + 1 
    mn1x=mn1x*-1
end
if (sprt_mn1_y<0) then
    mn1y=math.floor(math.random() * 2) + 1 
end
if (sprt_mn1_y>924) then
    mn1y=math.floor(math.random() * 2) + 1 
    mn1y=mn1y*-1
end

-- ######################################################
sprt_mn2_x = sprt_mn2_x + mn2x
sprt_mn2_y = sprt_mn2_y + mn2y

if (sprt_mn2_x<0) then
    mn2x=math.floor(math.random() * 2)   + 1 
end
if (sprt_mn2_x>300) then
    mn2x=math.floor(math.random() * 2) + 1 
    mn2x=mn1x*-1
end
if (sprt_mn2_y<0) then
    mn2y=math.floor(math.random() * 2) + 1 
end
if (sprt_mn2_y>924) then
    mn2y=math.floor(math.random() * 2) + 1 
    mn2y=mn2y*-1
end

-- ######################################################
sprt_mn3_x = sprt_mn3_x + mn3x
sprt_mn3_y = sprt_mn3_y + mn3y

if (sprt_mn3_x<0) then
    mn3x=math.floor(math.random() * 2)   + 1 
end
if (sprt_mn3_x>300) then
    mn3x=math.floor(math.random() * 2) + 1 
    mn3x=mn3x*-1
end
if (sprt_mn3_y<0) then
    mn3y=math.floor(math.random() * 2) + 1 
end
if (sprt_mn3_y>924) then
    mn3y=math.floor(math.random() * 2) + 1 
    mn3y=mn1y*-1
end

-- ######################################################
sprt_mn4_x = sprt_mn4_x + mn4x
sprt_mn4_y = sprt_mn4_y + mn4y

if (sprt_mn4_x<0) then
    mn4x=math.floor(math.random() * 1)   + 1 
end
if (sprt_mn4_x>300) then
    mn4x=math.floor(math.random() * 1) + 1 
    mn4x=mn1x*-1
end
if (sprt_mn4_y<0) then
    mn4y=math.floor(math.random() * 1) + 1 
end
if (sprt_mn4_y>924) then
    mn4y=math.floor(math.random() * 1) + 1 
    mn4y=mn1y*-1
end

-- ######################################################
sprt_mn5_x = sprt_mn5_x + mn5x
sprt_mn5_y = sprt_mn5_y + mn5y

if (sprt_mn5_x<0) then
    mn5x=math.floor(math.random() * 1)   + 1 
end
if (sprt_mn5_x>300) then
    mn5x=math.floor(math.random() * 1) + 1 
    mn5x=mn1x*-1
end
if (sprt_mn5_y<0) then
    mn5y=math.floor(math.random() * 1) + 1 
end
if (sprt_mn5_y>924) then
    mn5y=math.floor(math.random() * 1) + 1 
    mn5y=mn1y*-1
end

if (sprt_boy_x<0) then
    boy=0.1 
    sprt_boy_flip=0
end
if (sprt_boy_x>924) then
   boy=-0.1
    sprt_boy_flip=1
end

sprt_boy_x=sprt_boy_x+boy

seti("sprt_boy_x",math.floor(sprt_boy_x))
seti("sprt_boy_flip",sprt_boy_flip)

--print("FIM ./test/update.lua")
