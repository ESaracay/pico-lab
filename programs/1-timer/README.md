## 1-timer
This is the non janky way of counting time. I believe this is the intended way of getting time however it has some bugs. The first one is that it is not very accurate when checking microseconds. You can verify this with your A+ and your code from the logic analyzer. Secondly, you will notice that when you load from flash the pico will stop blinking. For some reason things get corrputed when loading from flash. With all that setaside I'll outline the steps for how I stumbled upon this source of time.

## Step 1
