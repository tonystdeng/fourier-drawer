#include "compile.hpp"


std::string removeExtension(std::string path) {// ai generated
    size_t lastDot = path.find_last_of('.');
    size_t lastSlash = path.find_last_of("/\\");
    
    // Check if the dot is part of the filename, not the directory
    if (lastDot != std::string::npos && (lastSlash == std::string::npos || lastSlash < lastDot)) {
        return path.substr(0, lastDot);
    }
    return path; // No extension found
}

int compile(char * path,int hcn)
{// hcn: stands for half circle num, ex: hcn=50 means 101 circles
    hcn=std::abs(hcn);
    std::vector<sl::pointgraph> graphs=getPointgraph(path);
    std::vector<std::map<int,std::array<double,2>>> returns;// list of (list of cirles)
    for (sl::pointgraph f:graphs)
    {
        int pointNum=f.size();
        double dt=1./pointNum;
        std::map<int,std::array<double,2>> C;
        for (int n=-hcn;n!=hcn;n++)
        {
            std::array<double,2> Cn={0,0};
            for (int t=0;t<pointNum;t++)
            {
                double rotaionHolder =-n*2*M_PI*(t*dt);
                std::array<double,2> Cnpart=applyRotation(rotaionHolder,f[t][0],-f[t][1],dt);
                Cn[0]+=Cnpart[0];Cn[1]+=Cnpart[1];
            }
            C[n]=v2p(Cn[0],Cn[1]);
        }
        returns.push_back(C);
    }
    save(returns,std::string(path)+".dc",hcn);
    return 0;
}

void save(std::vector<std::map<int,std::array<double,2>>> pathes,std::string path,int hcn)
{
    std::ofstream file(path);

    for (std::map<int,std::array<double,2>> path : pathes)
    {
        file<<path[0][0]<<"\n"<<path[0][1]<<"\n"<<0<<"\n";
        for (int i=1;i<hcn+1;i++)
        {
            file<<path[i][0]<<"\n"<<path[i][1]<<"\n"<<i<<"\n";
            file<<path[-i][0]<<"\n"<<path[-i][1]<<"\n"<<-i<<"\n";
        }file<<"z\n";
    }
}

std::vector<sl::pointgraph> getPointgraph(char* path)
{
    std::vector<sl::pointgraph> info=sl::svg2points(sl::file2vector(sl::fileLoader(path)));// W stack?
    // for (sl::pointgraph &i:info){i=sl::simplify(i);}
    std::array<double, 7> repoinfo=sl::getrepoinfo(info);
    double xmin=repoinfo[1],ymin=repoinfo[3],xl=repoinfo[4],yl=repoinfo[5];
    info=sl::resizeRepo(info,xmin+xl/2,ymin+yl/2);// en
    return info;
}
std::array<double,2> applyRotation(double rotation,double x,double y,double dt)
{
    double newx=x*std::cos(rotation) - y*std::sin(rotation);
    double newy=x*std::sin(rotation) + y*std::cos(rotation);
    return {newx*dt,newy*dt};
}

std::array<double,2> v2p(double x,double y)
{// v2p stands for vector to polar
    double length=std::sqrt(x*x+y*y);
    double angle=std::atan2(y,x);
    return {angle,length};
}
