#include "experi.h"
#include "sse.h"
#include "dataloader.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

void experi::testfilter(std::string mp,std::string info){
    dataloader *dl = new dataloader();

    if(mp.length()==0)
    {
        mp="map8_8.txt";info="a.out";
    }
    dl->loader(mp,info);
    std::vector<std::pair<int,int>> treu=dl->coord;

    sse* ss=new sse(dl->map);
    std::vector<std::string> actions=dl->action;
    std::vector<std::string> evidence=dl->sense;
   /* ss->printP();
    for(int i=0;i<actions.size();i++)
    {
        std::cout<<actions.at(i);
    }
    */
	std::vector<std::pair<int, int>> res;
    for (int i = 0; i < 100; i++)
	{
		ss->filter(actions.at(i), evidence.at(i), 0, 1);
       // ss->printP();
		node nd= ss->findmlPos();
        //std::cout << nd.x << "," << nd.y << std::endl;

      //  std::cout << nd.val << std::endl;
		std::pair<int, int> co;
		co.first = nd.x;
		co.second = nd.y;
		res.push_back(co);
	}
   //std::cout <<"?????"<<std::endl;
    std::ofstream fi;
    fi.open("C:/Users/Yi Dang/Desktop/556/map/filterRes.txt",std::ofstream::app);
    for(int i=0;i<res.size();i++)
    {

      //  std::cout << res.at(i).first << "," << res.at(i).second << std::endl;
//std::cout <<dl->coord.at(1).first<< std::endl;
       int xx=res.at(i).first-treu.at(i).first;
       int yy=res.at(i).second-treu.at(i).second;
       xx=xx<0?-xx:xx;
       yy=yy<0?-yy:yy;
    //   std::cout <<xx+yy<<std::endl;
       fi<<xx+yy<<" ";
    }
    fi<<std::endl;
    fi.close();
    delete dl;
    delete ss;
std::cout <<"------------------------"<<std::endl;
}

void experi::test100()
{
    int no=10;
    std::string base="C:/Users/Yi Dang/Desktop/556/map/";
    for(int i=1;i<=no;i++)
    {
        char bu[20];
        _itoa(i,bu,10);
        std::string ii(bu);

        std::string mapp="";
                mapp+=base+"map"+ii+"/map"+ii+".txt";
std::cout<<mapp<<std::endl;
        for(int j=0;j<no;j++)
        {

            char bu1[20];
            _itoa(j,bu1,10);
            std::string jj(bu1);

             std::string info="";
             info+=base+"map"+ii+"/GTD"+ii+"_"+jj;
std::cout<<info<<std::endl;
             testfilter(mapp,info);
        }
    }
}

void experi::testm100()
{
    int no=10;
    std::string base="C:/Users/Yi Dang/Desktop/556/map/";
    for(int i=1;i<=no;i++)
    {
        std::cout<<i<<std::endl;
        char bu[20];
        _itoa(i,bu,10);
        std::string ii(bu);

        std::string mapp="";
                mapp+=base+"map"+ii+"/map"+ii+".txt";
std::cout<<mapp<<std::endl;
        for(int j=0;j<no;j++)
        {

            char bu1[20];
            _itoa(j,bu1,10);
            std::string jj(bu1);

             std::string info="";
             info+=base+"map"+ii+"/GTD"+ii+"_"+jj;
std::cout<<info<<std::endl;
             testmle(mapp,info);
        }
    }
}

void experi::truecellp100()
{
    int no=10;
    std::string base="C:/Users/Yi Dang/Desktop/556/map/";
    for(int i=1;i<=no;i++)
    {
        std::cout<<i<<std::endl;
        char bu[20];
        _itoa(i,bu,10);
        std::string ii(bu);

        std::string mapp="";
                mapp+=base+"map"+ii+"/map"+ii+".txt";
std::cout<<mapp<<std::endl;
        for(int j=0;j<no;j++)
        {

            char bu1[20];
            _itoa(j,bu1,10);
            std::string jj(bu1);

             std::string info="";
             info+=base+"map"+ii+"/GTD"+ii+"_"+jj;
std::cout<<info<<std::endl;
             truecellp(mapp,info);
        }
    }
}
void experi::truecellp(std::string mp,std::string info){
    dataloader *dl = new dataloader();

    if(mp.length()==0)
    {
        mp="map8_8.txt";info="a.out";
    }
    dl->loader(mp,info);
    std::vector<std::pair<int,int>> treu=dl->coord;

    sse* ss=new sse(dl->map);
    std::vector<std::string> actions=dl->action;
    std::vector<std::string> evidence=dl->sense;


    std::vector<std::pair<int, int>> res;
    std::ofstream fi;
    fi.open("C:/Users/Yi Dang/Desktop/556/map/truecellp.txt",std::ofstream::app);
    for (int i = 0; i < 100; i++)
    {
        ss->filter(actions.at(i), evidence.at(i), 0, 1);
       // ss->printP();
        //node nd= ss->findmlPos();


        int va=ss->map[treu.at(i).first][treu.at(i).second].val*1000;
            fi<<va<<" ";
        //std::cout << nd.x << "," << nd.y << std::endl;

      //  std::cout << nd.val << std::endl;

    }
   //std::cout <<"?????"<<std::endl;


    fi<<std::endl;
    fi.close();
    delete dl;
    delete ss;


}
void experi::testmle(std::string mp,std::string info)
{
    dataloader *dl = new dataloader();

    if(mp.length()==0)
    {
        mp="map8_8.txt";info="a.out";
    }
    dl->loader(mp,info);
    std::vector<std::pair<int,int>> treu=dl->coord;

    sse* ss=new sse(dl->map);
    std::vector<std::string> actions=dl->action;
    std::vector<std::string> evidence=dl->sense;
 //   std::cout<<"here1"<<std::endl;
   /* ss->printP();
    for(int i=0;i<actions.size();i++)
    {
        std::cout<<actions.at(i);
    }
    */
    std::string ac="";
    std::string ev="";
    for(int i=0;i<100;i++){
        ac+=actions.at(i);
        ev+=evidence.at(i);
    }
/*for(int i=0;i<120;i++){
    for(int j=0;j<160;j++){
    std::cout<<ss->map[i][j].val;

    }
     std::cout<<std::endl;
}*/

    std::cout<<ss->m<<ss->n<<std::endl;
 //   ss->printP();

    std::vector<std::pair<int, int>> res;
  //  std::cout<<actions.size()<<345345345<<std::endl;
   // ss->printP();


    ss->mle(ac,ev, 0, 100);
std::vector<std::pair<int,int>> ob=ss->findmle(100);



   // ss->mleappr(ac,ev, 0, 10);
//ss->printP();
   // std::cout<<actions.size()<<345345345<<std::endl;
   // ss->printP();
   //  std::cout<<ss->map[0][0].parents.size()<<"123123123"<<std::endl;


//std::vector<std::pair<int,int>> ob=ss->findmle(100);
 //std::cout<<ss->map[0][2].parents.size()<<std::endl;
 //std::cout<<ob.size()<<std::endl;

std::ofstream fi;
fi.open("C:/Users/Yi Dang/Desktop/556/map/mleRes.txt",std::ofstream::app);

    for(int i=0;i<100;i++){
        int xx=ob.at(99-i).first-treu.at(i).first;
        int yy=ob.at(99-i).second-treu.at(i).second;
        xx=xx<0?-xx:xx;
        yy=yy<0?-yy:yy;
       // std::cout<<xx+yy<<std::endl;
         fi<<xx+yy<<" ";
    }
    fi<<std::endl;
    fi.close();
delete dl;
    delete ss;
}

void experi::find10(std::string mp,std::string info,int no){
    dataloader *dl = new dataloader();
if(no<0) no=100;
    if(mp.length()==0)
    {
        mp="map8_8.txt";info="a.out";
    }
    dl->loader(mp,info);
    std::vector<std::pair<int,int>> treu=dl->coord;

    sse* ss=new sse(dl->map);
    std::vector<std::string> actions=dl->action;
    std::vector<std::string> evidence=dl->sense;
 //   std::cout<<"here1"<<std::endl;
   /* ss->printP();
    for(int i=0;i<actions.size();i++)
    {
        std::cout<<actions.at(i);
    }
    */
    std::string ac="";
    std::string ev="";
    for(int i=0;i<100;i++){
        ac+=actions.at(i);
        ev+=evidence.at(i);
    }
/*for(int i=0;i<120;i++){
    for(int j=0;j<160;j++){
    std::cout<<ss->map[i][j].val;

    }
     std::cout<<std::endl;
}*/

    //std::cout<<ss->m<<ss->n<<std::endl;
 //   ss->printP();

  //  std::vector<std::pair<int, int>> res;
  //  std::cout<<actions.size()<<345345345<<std::endl;
   // ss->printP();
ss->mle(ac,ev, 0, no);

  std::vector<std::vector<std::pair<int,int>>> res=  ss->find10();
  for(int i=0;i<res.size();i++)
  {
      std::vector<std::pair<int,int>> th=res.at(i);
      for(int j=0;j<th.size();j++){
          std::pair<int,int> pa=th.at(j);
          std::cout<<pa.first<<","<<pa.second<<" ";
      }
      std::cout<<std::endl;
  }

}

