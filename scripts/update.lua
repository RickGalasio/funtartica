--print("START ./test/update.lua")
sprt_sheep_x = sprt_sheep_x + sheepincx
sprt_sheep_y = sprt_sheep_y + sheepincy

if (sprt_sheep_x<0) then
    sheepincx=(math.random() )  
    sprt_sheep_flip=1
end
if (sprt_sheep_x>924) then
    sheepincx=(math.random()) *-1
    sprt_sheep_flip=0
end
if (sprt_sheep_y<0) then
    sheepincy=(math.random() )
end
if (sprt_sheep_y>324) then
    sheepincy=(math.random())
    sheepincy=sheepincy*-1
end

-- ######################################################
sprt_mn1_x = sprt_mn1_x + mn1x
sprt_mn1_y = sprt_mn1_y + mn1y

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

--print("sprt_boy_x:")
--print(sprt_boy_x)
--print("sprt_boy_y:")
--print(sprt_boy_y)

seti("sprt_boy_x",math.floor(sprt_boy_x))
seti("sprt_boy_flip",sprt_boy_flip)

seti("sprt_sheep_x",math.floor(sprt_sheep_x))
seti("sprt_sheep_y",math.floor(sprt_sheep_y))
seti("sprt_sheep_flip",sprt_sheep_flip)

seti("sprt_mn1_x",math.floor(sprt_mn1_y))
seti("sprt_mn1_y",math.floor(sprt_mn1_x))

seti("sprt_mn2_x",math.floor(sprt_mn2_y))
seti("sprt_mn2_y",math.floor(sprt_mn2_x))

seti("sprt_mn3_x",math.floor(sprt_mn3_y))
seti("sprt_mn3_y",math.floor(sprt_mn3_x))

seti("sprt_mn4_x",math.floor(sprt_mn4_y))
seti("sprt_mn4_y",math.floor(sprt_mn4_x))

seti("sprt_mn5_x",math.floor(sprt_mn4_y))
seti("sprt_mn5_y",math.floor(sprt_mn4_x))
--print("FIM ./test/update.lua")
