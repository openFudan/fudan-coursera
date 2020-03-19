import vtk

def main():
    #选定想要渲染的几何体，并确定其基本数据
    cylinder = vtk.vtkCylinderSource()
    cylinder.SetHeight(3.0)  
    cylinder.SetRadius(1.0)  
    cylinder.SetResolution(6) 

    cylinderMapper = vtk.vtkPolyDataMapper()  # 渲染多边形几何数据
    cylinderMapper.SetInputConnection(cylinder.GetOutputPort())  
    cylinderActor = vtk.vtkActor()
    cylinderActor.SetMapper(cylinderMapper)  # 设置生成几何图元的Mapper。
    renderer = vtk.vtkRenderer()  # 负责管理场景的渲染过程
    renderer.AddActor(cylinderActor)
    renderer.SetBackground(0.1, 0.2, 0.4)
    renWin = vtk.vtkRenderWindow()  # 将操作系统与VTK渲染引擎连接到一起。
    renWin.AddRenderer(renderer)
    renWin.SetSize(300, 300)
    iren = vtk.vtkRenderWindowInteractor()  # 提供平台独立的响应鼠标、键盘和时钟事件的交互机制
    iren.SetRenderWindow(renWin)

    # 交互器样式的一种，该样式下，用户是通过控制相机对物体作旋转、放大、缩小等操作
    style = vtk.vtkInteractorStyleTrackballCamera()

    iren.SetInteractorStyle(style)
    iren.Initialize()

    iren.Start()

    # Clean up
    del cylinder
    del cylinderMapper
    del cylinderActor
    del renderer
    del renWin
    del iren


main()

