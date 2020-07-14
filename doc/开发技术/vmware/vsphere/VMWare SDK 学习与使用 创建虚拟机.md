http://blog.csdn.net/ABBuggy/article/details/6338756

操作对象：Folder

调用方法：createVM_Task

功能：

在一个floder中创建一个virtual machine并将其加入到某个resource pool中。如果你想创建创建templates就不能用这个方法了，而是将virtual machine标记为templeates或克隆成一个templates。要注意一点，操作的那个folder下，必须可以放置virtual machine。

参数：

_this：ManagedObjectReference （Folder）类型。目标folder，新建的virtual machine将被创建在这个folder下面。

config：VirtualMachineConfigSpec 类型，在这里设置新建的virtual machine的硬件属性。

pool：ManagedObjectReference （ResourcePool）类型。新建的virtual machine被指派的resource pool。

host：ManagedObjectReference （HostSystem）类型。新建的virtual machine运行的host。这个host必须和指派的resource pool在同一个ComputeResource中。
