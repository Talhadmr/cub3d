deltaDistX ve deltaDistY Hesaplaması:
Metinde, ışın izleme algoritmasında kullanılan deltaDistX ve deltaDistY değerlerinin geometrik türetilmesi açıklanıyor. Pythagoras teoremi kullanılarak, bu değerler şu şekilde hesaplanıyor:

\text{deltaDistX} = \sqrt{1 + \frac{{\text{rayDirY}^2}}{{\text{rayDirX}^2}}}deltaDistX= 
1+ 
rayDirX 
2
 
rayDirY 
2
 

\text{deltaDistY} = \sqrt{1 + \frac{{\text{rayDirX}^2}}{{\text{rayDirY}^2}}}deltaDistY= 
1+ 
rayDirY 
2
 
rayDirX 
2
 
​
 
​
 

Ancak, bu ifadeler daha sonra aşağıdaki gibi daha basitleştirilmiş hallerine getiriliyor:

\text{deltaDistX} = \frac{{|\text{rayDir}|}}{{\text{rayDirX}}}deltaDistX= 
rayDirX
∣rayDir∣
​
 

\text{deltaDistY} = \frac{{|\text{rayDir}|}}{{\text{rayDirY}}}deltaDistY= 
rayDirY
∣rayDir∣
​
 

Burada, |\text{rayDir}|∣rayDir∣ vektörün uzunluğunu ifade eder (yani, \sqrt{\text{rayDirX}^2 + \text{rayDirY}^2} 
rayDirX 
2
 +rayDirY 
2
 
​
 ).

DDA Algoritması ve İlerleme (stepX ve stepY):
DDA (Digital Differential Analyzer) algoritması, her döngüde tam olarak bir kare atlayacak şekilde tasarlanmış bir algoritmadır. İlerlemenin x-y düzlemindeki yönlere bağlı olarak -1 veya +1 olacak şekilde stepX ve stepY değişkenlerine atanması anlatılıyor. Bu değişkenler, ray'ın hareket yönünü belirtir.

hit ve side Değişkenleri:
hit değişkeni, bir sonraki döngünün bitirilip bitirilemeyeceğini belirlemek için kullanılır. side değişkeni ise bir duvarın x-kenarı mı, y-kenarı mı vurulduğunu belirtir. Eğer x-kenarı vurulduysa, side 0 olarak ayarlanır; eğer y-kenarı vurulduysa, side 1 olarak ayarlanır. Bu durumlar, ızgara üzerindeki karelerin sınırlarını ifade eder.

Bu metin, ışın izleme algoritmasının temel adımlarını ve bu adımların nasıl hesaplandığını açıklamaktadır.


When deriving deltaDistX geometrically you get, with Pythagoras, the formulas below. For the blue triangle (deltaDistX), one side has length 1 (as it is exactly one cell) and the other has length raydirY / raydirX because it is exaclty the amount of units the ray goes in the y-direction when taking 1 step in the X-direction. For the green triangle (deltaDistY), the formula is similar.
deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))

But this can be simplified to:

deltaDistX = abs(|rayDir| / rayDirX)
deltaDistY = abs(|rayDir| / rayDirY)

Where |rayDir| is the length of the vector rayDirX, rayDirY (that is sqrt(rayDirX * rayDirX + rayDirY * rayDirY)): you can indeed verify that e.g. sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)) equals abs(sqrt(rayDirX * rayDirX + rayDirY * rayDirY) / rayDirX). However, we can use 1 instead of |rayDir|, because only the *ratio* between deltaDistX and deltaDistY matters for the DDA code that follows later below, so we get:

deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)

Due to this, the deltaDist and sideDist values used in the code do not match the lengths shown in the picture above, but their relative sizes all still match.

[thanks to Artem for spotting this simplification]

The variable perpWallDist will be used later to calculate the length of the ray.

The DDA algorithm will always jump exactly one square each loop, either a square in the x-direction, or a square in the y-direction. If it has to go in the negative or positive x-direction, and the negative or positive y-direction will depend on the direction of the ray, and this fact will be stored in stepX and stepY. Those variables are always either -1 or +1.

Finally, hit is used to determinate whether or not the coming loop may be ended, and side will contain if an x-side or a y-side of a wall was hit. If an x-side was hit, side is set to 0, if an y-side was hit, side will be 1. By x-side and y-side, I mean the lines of the grid that are the borders between two squares.



