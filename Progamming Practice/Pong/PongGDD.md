**Name: Pong**
**Description:**
Pong is a game based in two sides, each side controlled by a player (later add some option for just 1 player to be necessary to play)
And each player controles a pad, this pad can be moved by the player up and down
A ball starts in the middle in a random direction and the goal is to make the ball to touch the other side.
This will add 1 point to the player on the other side that the ball just touched, **e.g.:**

* If you are controlling the pad on the left and touch the ball sending it to the right side and it touches the right border this will add 1 point to the left side.
  The goal is to have more points than your opponent



**Technical Aspects of the Game**
**My initial vision:**
I am trying to make pong from scratch in C, and I really want to learn from 0, I am new to this and don't know much about coding in general.


I have 4 "walls" or borders, I have upper, bottom, left and right, and this is like the ("layout?"), then I have the Lpad or pad1 and the Rpad or pad2, and also I have the ball



So, imagine that my borders are in 5 lines, and it has a 30 spaces of length, so the ball is set in the 3rd line on the 15th space, now (the ball being half of a line of tall) I could set that space as the coordinates (0;0) and create a **coordinate system** from that.



This said I could define the **movement** based on this system of coordinates, the pads (being 2 lines height, and 1 line of length) could only move in the Y coordinates and not in the X coordinates, meaning that they would move only between the 5 lines), this could work as a each time the user press a certain key from the keyboard the pad saves the current position of the pad, then cleans the pad and then rewrites it on the upper or down line according to the key pressed being up or down (this means that if the keys for movement are W for up and S, each time that the user presses W the pad assigned to that key should rewrite on the upper line).



The **point system** should be two ceros, (each cero representing each player, one cero for the Lplayer and 0 cero for Rplayer) and it will set the count for who is winning.



With the previous explained coordinates system I could use **angles** to move the ball **at the start**, making that the ball don't just go in a straight line.


Now I could set some ground rules for the ball, like the ball should bounce on the upper and bottom borders.
When the ball hit L or R borders it should add 1 point to the "pad"(player) on the other side that (meaning that if the ball hits the L border it adds 1 point to the "Rpad" or "Rplayer").



##### **New Changes and recommendations:**

Start by defining your game world using a coordinate system where (0, 0) is the top-left corner of the screen, with X increasing to the right and Y increasing downward. This is the standard convention in most graphics and console systems. Instead of setting the ball's starting position as (0, 0), place it near the center of the playfield, such as (15, 3) in your 30x5 grid, but note that a height of only 5 lines is extremely limiting and may make gameplay difficult; typical console implementations use a much taller grid.



For ball movement, instead of using angles directly, it's simpler to use velocity components (dx, dy). For example, ball\_x += ball\_dx; ball\_y += ball\_dy;. When the ball hits the top or bottom wall (Y <= 0 or Y >= HEIGHT), reverse the Y velocity: ball\_dy = -ball\_dy;. This simulates bouncing.



When the ball collides with a paddle, reverse the X velocity (ball\_dx = -ball\_dx) and optionally adjust the Y velocity based on where the ball hit the paddle—hitting near the top imparts upward velocity, the center imparts no vertical change, and the bottom imparts downward. One method is to calculate the relative hit position and scale the Y velocity accordingly.



If the ball exits the left or right edge of the screen, award a point to the opposite player, as you correctly identified. Maintain two score variables, one for each player, and display them on screen.



Better approach: Use a top-left origin (0,0), not center-based coordinates—this matches console systems.





