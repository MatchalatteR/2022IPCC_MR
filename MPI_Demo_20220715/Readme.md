# Before you compile

——这两个程序是一个简单的积分计算PI值的C语言程序

```c++
/*********************
运行环境：Linux

编译命令：make

运行命令：
./No_MPI_Version
mpirun -np 11 MPI_Version
**********************/
```

### 说明：

此程序仅仅使用了最基础的并行分组进行计算。

针对下一步的练习，我们在实际使用过程中不可避免的会接触到数据之间相互关联的问题，而这需要对进程之间的发送接收进行一定的设计

计算π值的简单积分公式
$$
π/4 = ∫_0^1√1-x^2
$$




e.g:

#### **两个数组a和b， 每个数组大约2000万个数，a[i]=sin(i), b[i]=sin(i+5).**

**数组描述**
**1. 计算数组平均值 Mean**

![平均值](https://img-blog.csdn.net/20171108224056686?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzQyNjYwMw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
**2. 计算标准偏差 Standard deviation**

![标准偏差](https://img-blog.csdn.net/20171108224158094?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzQyNjYwMw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
**3. 最后计算皮尔森相关系数 Pearson correlation coefficient**

![皮尔森相关系数](https://img-blog.csdn.net/20171108224346183?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvdTAxMzQyNjYwMw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

### **SP.**

1. 普通算法计算出皮尔森相关系数，记录运行时间
2. MPI算法计算出皮尔森相关系数，记录运行时间
3. 
3. 比较两种算法所花时间，得出速度提升











slrum sbatch

