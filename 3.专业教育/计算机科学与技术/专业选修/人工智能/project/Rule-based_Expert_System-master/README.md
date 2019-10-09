## 基于规则的专家系统 -- 图形检测
### 前言
此项目是**人工智能**的课程项目。具体要求为实现一个*基于规则的专家系统*， 用来进行简单直线型几何图形的形状检测。  
项目实现的重点在于**规则的表示**， **推理引擎的构建**， **知识库的构建**， **图片的预处理** 和 **用户界面**。  
项目实现语言为Python，图片预处理用到了OpenCV， 用户界面用到了wxPython。  
专家系统的设计参考了[《人工智能 - 智能系统指南》(原书第3版)](https://book.douban.com/subject/11606478/) 第2章。    
如有任何对项目的改进建议，欢迎评论。 :~) 

### 目录
1. [概述](#general)
2. [图形检测专家系统的结构](#structure)
3. [规则的构建和表示](#rule)
4. [知识库的表示](#knowledge)
5. [图片的预处理](#pic_handle)
6. [数据库的表示](#fact)
7. [推理引擎的构建 : 后向链接推理技术](#back)
8. [用户界面](#GUI)
9. [测试用例](#test)
10. [总结](#conclusion)
11. [附录](#addition)

### <a name='general'></a>概述
图形检测专家系统的运作流程为：  

* 通过图片预处理得到一组基本事实（即图形中各线段端点坐标）
* 处理这一组基本事实，产生专家系统的数据库
* 推理引擎读取外部的规则文档，产生知识库
* 推理引擎读入数据库
* 采用后向链接推理技术进行推理
* 推理过程中记录触发的规则和符合规则的事实
* 绘制出用户所要检测的图形的位置
* 在用户界面中显示出来  

图形检测专家系统还提供另外的功能，包括：

* 提供规则编辑器，用于增添新的规则
* 展示目前的规则库
* 展示当前检测图片的事实库 

图形检测专家系统目前支持检测的图形包括：

* 三角形
    * 锐角三角形
    * 直角三角形
    * 钝角三角形
    * 等腰三角形
        * 直角等腰三角形
        * 锐角等腰三角形
        * 钝角等腰三角形
    * 等边三角形
* 四边形
    * 平行四边形
        * 矩形
            * 正方形
        * 菱形
    * 梯形
        * 等腰梯形
        * 直角梯形      
* 五边形
    * 正五边形
* 六边形
    * 正六边形

图形检测专家系统支持不同位置，各种形态，各种大小的图形检测，且支持一张图片多个图形的检测。

### <a name='structure'></a>图形检测专家系统的结构
图形检测专家系统的结构尽可能模仿了书中展示的**基于规则的专家系统的基本结构**。  
具体结构如下：  
![structure](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/structure.png)  
图形检测专家系统也由5部分组成：[知识库Knowledge base](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/rules/rules.txt), [数据库Database](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/facts/facts.txt), [推理引擎Inference engine](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/engine/inference_engine.py), [解释设备Explanation facilities, 用户界面User interface](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/GUI/main_frame.py).  
对应的项目文件夹分别为rules, facts, engine, GUI。  
另外，由于图形的特殊性，项目文件中还包含[图片预处理器](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/Picture_handler/cv_handler2.py).

### <a name='rule'></a>规则的构建和表示
因为专家系统需要支持动态的加载知识库，所以检测规则不能硬编码在程序中，而是需要长期存储在外部文件中，并在推理引擎中加载。  
基于以上原因，首先构建了一个Rule类用来表示某条规则。Rule类包含id(规则编号), antecedent(规则前项), consequent(规则后项), description(规则描述) 这四个类成员。  
其中， 考虑到图形检测规则的特点，规则前项之间用 ***与*** 逻辑连接。  
一条典型的规则如下所示：
> {  
IF: ['the shape is triangle', 'lines are all equal']  
THEN: 'the shape is equilateral triangle'  
DESCRIPTION: 'equilateral triangle'  
}  

以上规则用来判断一个图形是等边三角形。  
其他的规则也类似。  
在用户界面部分提供了规则编辑器的功能，能够在现有的知识库文件的基础上添加新的规则。

### <a name='knowledge'></a>知识库的表示
知识库也就是此图形检测专家系统的规则集合。知识库以 txt格式存储，包含了判断图形所需的所有规则。  
程序运行时，推理引擎从该知识库文件中读取所有规则，并相应地构建所有规则的Rule实例。

### <a name='pic_handle'></a>图片的预处理
此图形检测专家系统的直接输入是要检测的图片。为了得到关于图片的数据库，首先需要对图片进行一定程度的预处理。  
采用的图片处理库是OpenCV，分别尝试了两种得到数据的方法：  

*  霍夫变换：`cv2.HoughLines2()`
*  轮廓检测：`cv2.findContours()`

1. 霍夫变换：  
    霍夫变换比较基础，能够得到图片中所有线段的端点坐标。  
    但是霍夫变换存在几个比较明显的问题：
    * 参数很难调：在最初的霍夫变换检测线段的尝试中，不同的参数会得到不同的线段集合，不同的图片在同一个参数下检测出来的线段集合质量也参差不齐，很难找到一个合适的霍夫变换参数
    * 调整霍夫变换的结果很麻烦：由于得到的线段端点并不很精确，故需要再人为地判断这些端点之间的关系。  
    如判断两个端点是否足够临近，以致能够认为是同一个端点时，需要人为地设置一个临近阈值。但是该临近阈值对于不同的图片有不同的判断结果。有时候阈值太大，以至于将非同一个端点误判为同一个端点，而有时候阈值太小，以至于没有将所有临近端点都判断出来。  
    这个问题在图片预处理中很关键，尤其是在判断两直线夹角时。
    * 当图片中有多个图形时，处理遇到瓶颈：由于霍夫变换得到的是图片中 **所有** 的线段，而不能区分哪些线段属于哪一个图形，故需要另外人为判断线段集合的图形归属问题。这带来了很大的工作量。  

    基于以上问题，和实际尝试中不尽如人意的检测结果，决定放弃使用霍夫变换作为图片预处理的手段。  
2. 轮廓检测：  
    轮廓检测也比较基础，相对来说还比霍夫变换简单许多。轮廓检测也是得到线段的端点坐标。但不同于霍夫变换，轮廓检测返回的结果是图形的轮廓顶点（需要经过一个近似的步骤`cv2.approxPolyDP()`）。  
    也就是说，图片中每个图形都有各自的顶点。更进一步，可以从顶点得到图形的所有边和边与边的关系（夹角大小，是否平行等）。通过这些预处理步骤，可以得到关于图片的基础事实，用来构成以下的数据库。  
    因为 **轮廓检测的返回值不再有临近端点归并问题， 线段集合的图形归属问题**， 所以最终的图片预处理技术以轮廓检测为基础。 
    
在图片的预处理这一步走了很多弯路，但最终得到了满意的处理结果。

### <a name='fact'></a>数据库的表示
数据库以轮廓为单位，包含了每个轮廓中所有边和角的关系。  
抽象来讲，数据库包含了每个图形的基本事实。  
一个典型的数据库如下：  
> Contour #0  
{  
--About Lines-- 4 lines  
<  
2 lines are equal  
(84, 156)-->(365, 155): Length: 281.00, Angle:-0.20  
(366, 252)-->(85, 253): Length: 281.00, Angle:-0.20  
\>  
<
4 closure lines  
(84, 156)-->(365, 155): Length: 281.00, Angle:-0.20  
(365, 155)-->(366, 252): Length: 97.01, Angle:89.41  
(366, 252)-->(85, 253): Length: 281.00, Angle:-0.20  
(85, 253)-->(84, 156): Length: 97.01, Angle:89.41  
\>  
--About Angles--  
<  
1 angle is right angle  
(84, 156)-->(365, 155): Length: 281.00, Angle:-0.20  
(365, 155)-->(366, 252): Length: 97.01, Angle:89.41  
\>  
<  
2 pairs of parallel lines  
(84, 156)-->(365, 155): Length: 281.00, Angle:-0.20  
(366, 252)-->(85, 253): Length: 281.00, Angle:-0.20  
(365, 155)-->(366, 252): Length: 97.01, Angle:89.41  
(85, 253)-->(84, 156): Length: 97.01, Angle:89.41  
\>    
}  
Contour #1  
{  
--About Lines-- 3 lines  
some line facts  here  
--About Angles--  
some angle facts  here  
}

以上数据库是测试用例产生的数据库的一部分。  
数据库一方面用来检查图片预处理的准确度，另一方面也用来展示给用户查看。

### <a name='back'></a>推理引擎的构建 : 后向链接推理技术
1. 前向链接和后向链接的抉择：  
    正如书上给的建议，首先分析我们判定图形形状时解决问题的方式。  
    如果要我们判定一个图形，比方说判定一个正方形，我们首先会证实是否是矩形，然后四边是否长度相等。这样的推理方式是从一个假设出发，去找论据，也即后向链接的推理技术。  
    另一方面，从项目目标的角度考虑，需要用户选择要检测的图形，然后推理引擎查找相关的事实来支持要检测的假设。所以这也要求图形检测专家系统使用后向链接技术的推理引擎。
    后向链接是目标驱动的推理技术，从复杂度上讲，后向链接比前向链接更高效，因此后向链接也会是推理技术的首选。
2. 后向链接的实现：  
    参考书上给的后向链接推理技术的例子，后向链接推理的实现需要有 ***栈结构***。  
    在推理引擎的实现中，使用了Python的list类型数据结构来模拟栈的操作，提供了 *将条件压入推理栈*， *弹出推理栈栈顶条件*， *获取推理栈栈顶条件*， *判断推理栈是否为空* 四个栈操作。  
3. 推理引擎的推理机制:
    * 首先，推理引擎在启动时会加载规则库和数据库，只要检测的图片不变，加载的规则库和数据库就不再重新载入。  
    * 之后，根据用户想要检测的形状，设置推理引擎的推理目标，作为第一个压入推理栈的条件。
    * 然后，启动推理引擎。
        * Step1:取出推理栈栈顶条件，去和规则库中的规则后项进行匹配。如果匹配成功，则获得该条匹配的规则的所有前项。如果匹配失败，表示所有规则都不适用，直接退出后向链接推理循环。
        * Step2:将所有前项逐条和数据库中的事实进行匹配。如果匹配，则说明该前项已经在数据库中被满足，如果不匹配，则说明该前项也是推理的条件之一，将其压入推理栈。对匹配的规则的所有前项都执行这样的操作。
        * Step3:重复执行上述Step1和Step2操作，直到遇到下面两种情况：
            * 推理栈为空，则说明所有推理已进行彻底，推理目标可达，该目标的后向链接推理成功。
            * 没有能够匹配的规则，则说明没有充分的事实来支持推理目标，推理目标不可达，该目标的后向链接推理失败。

### <a name='GUI'></a>用户界面
用户界面包含了以下部分：

* 源图片
* 检测结果的展示图片
* 检测结果的成功或失败报告
* 检测过程中被匹配的事实
* 检测过程中被触发的规则
* 能够检测的图形的树形列表
* 选择原图片的按钮
* 打开规则编辑器的按钮
*  展示所有规则的按钮
*  展示所有关于源图片的事实的按钮

用户主界面如下图所示：  
![main](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/main.png)  
规则编辑界面如下图所示：  
![editor](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/editor.png)  
展示所有规则和所有事实的界面如下图所示：  
![rule_fact](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/rule_fact.png)

### <a name='test'></a>测试用例
#### A. 单个图形的测试：
1. 三角形：  
    ![triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/triangle.png)  
    * 锐角三角形：  
        ![acute_triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/acute_triangle.png)
    * 直角三角形：  
        ![right_triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/right_triangle.png)
    *  钝角三角形：  
        ![obtuse_triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/obtuse_triangle.png)
    *  等腰三角形：  
        ![isosceles_triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/isosceles_triangle.png)
        * 等腰直角三角形：  
            ![right ang isosceles triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/right_and_isosceles_triangle.png)
        *  等腰锐角三角形：  
            ![acute and isosceles triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/acute_and_isosceles_triangle.png)
        *  等腰钝角三角形：  
            ![obtuse and isosceles triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/obtuse_and_isosceles_triangle.png)
    * 等边三角形：  
        ![equilateral_triangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/equilateral_triangle.png)
2. 四边形：  
    ![quadrilateral](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/quadrilateral.png)  
    * 平行四边形：  
        ![parallelogram](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/parallelogram.png)    
        * 矩形：   
            ![rectangle](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/rectangle.png)    
            * 正方形：  
                ![square](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/square.png)
        *  菱形：  
            ![rhombus](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/rhombus.png)
    * 梯形：  
        ![trapezoid](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/trapezoid.png)  
        * 等腰梯形：  
            ![isosceles_trapezoid](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/isosceles_trapezoid.png)
        * 直角梯形：  
            ![right_trapezoid](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/right_trapezoid.png) 
3. 五边形：
    ![pentagon](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/pentagon.png)
    * 正五边形：  
    ![regular_pentagon](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/regular_pentagon.png)
4. 六边形：  
    ![hexagon](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/hexagon.png)
    * 正六边形：   
    ![regular_hexagon](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/regular_hexagon.png)
    
#### B. 混合图形的测试：
* ![mix10](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix10.png)  
  ![mix11](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix11.png)
* ![mix20](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix20.png)  
  ![mix21](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix21.png)
* ![mix30](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix30.png)  
   ![mix31](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix31.png)  
   ![mix32](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix32.png)
* ![mix40](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix40.png)  
   ![mix41.png](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/readme_picture/mix41.png)

### <a name='conclusion'></a>总结
图形界面中的 *Matched Facts文本框* 和 *Hit Rules文本框* 可以作为此图形检测专家系统的解释设备。  
以上即是图形检测专家系统的全部内容。  
其中推理引擎稍作改进可以作为一个通用的后向链接推理的专家系统框架。

### <a name='addition'></a>附录
此图形检测专家系统的知识库： [知识库](https://github.com/Sorosliu1029/Rule-based_Expert_System/blob/master/rules/rules.txt)  
此图形检测专家系统的Github托管网址：[Github](https://github.com/Sorosliu1029/Rule-based_Expert_System)
