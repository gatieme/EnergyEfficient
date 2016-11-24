#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QDebug>

class Singleton : public QObject
{
    Q_OBJECT
public:

signals:

public slots:

    ///////////////////////////////////////////////////////////////////
    /// 3--CPU
    ///////////////////////////////////////////////////////////////////
    /////////////////////
    //  3.1--获取编号为cpuid的CPU-freq的信息
    /////////////////////
    QList<unsigned long> UpdateAllCpusScalingCurFrequency( );   //  CPU的当前运行频率
    QList<unsigned long> UpdateAllCpusCpuInfoCurFrequency( );   //  当前运行频率
    /////////////////////
    //  3.2--获取编号为cpuid的CPU-usage的信息
    /////////////////////

    QList<double> UpdateAllCpusUsage( );                 //  当前运行频率
public :
    static Singleton* GetInstance( )           // 获取对象单例的指针
    {
        if(Singleton::m_singleton == NULL)       // 如果单例对象没有创建， 则将其创建
        {
            Singleton::m_singleton = new Singleton( );
        }
    }
private :
    explicit Singleton(QObject *parent = 0) // 构造函数[被保护]
    {
    }

    Singleton(const Singleton &singleton)       // 赋值构造函数[被保护]
    {
        qDebug( ) <<1221 <<endl;
    }

    ~Singleton( )
    {
    }


    static Singleton *m_singleton;                // 指向单例对象的指针

};

#endif // SINGLETON_H
