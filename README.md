# Color converter 
##Review
This application convert colors between HSV, RGB and XYZ models and give users ability to chose color with dialog 

##Interface
###1.Spinboxes with models values
  User can change values and it will be autoconverted to other models
  User can't enter unvalid values

###Models
1) RGB
   red 0 - 255, green 0 - 255 , blue 0 - 255
2) HSV
   hue 0 - 359, saturation 0 - 255, value 0 - 255
3) XYZ
   x 0 - 100, y 0 - 100, z 0 - 100

###2.Dialog
To open dialog user should to push "Show dialog" button
In dialog user can choose color with
    1) Palette
    2) HTML code of color
    3) Used earlier colors table
    4) Basic colors table
    5) Picking any screen color
    6) By rgb or hsv values
Application will show all models values of choosed color

##3.Warning
  There are some troubles with converting hsv and rgb to xyz and vice versa
  if convertion is not accurate, application will say about it with label under the widget with color

##4.Technologies
  This project is writen with Qt Creator version 5.14.2 by c++ programming language


  Enjoi it!
