#include <iostream>

#include "graph.h"
#include "kernigan_lin.h"

int main(){
        Graph *temp=new Graph();
        temp->add_vertex("a");
        temp->add_vertex("b");
        temp->add_vertex("c");
        temp->add_vertex("d");
        temp->add_vertex("e");
        temp->add_vertex("f");
        temp->add_vertex("g");
        temp->add_vertex("h");
        temp->add_edge("a","b",20);
        temp->add_edge("a","d",80);
        temp->add_edge("a","g",90);
        temp->add_edge("b","f",10);
        temp->add_edge("b","e",10);
        temp->add_edge("c","f",50);
        temp->add_edge("c","h",20);
        temp->add_edge("c","d",10);
        temp->add_edge("d","g",20);
        temp->add_edge("e","b",50);
        temp->add_edge("e","g",30);
        temp->add_edge("f","c",10);
        temp->add_edge("f","d",40);
        temp->add_edge("g","a",20);
        std::cout << std::endl;
        temp->print();
        /*temp->BFS("a");
        temp->mst_kruskal();
        std::cout << std::endl;
        temp->mst_prim("f");
        std::map<std::string, std::pair<int, std::string> > distance = temp->Dijkstra("a");
        std::cout<<"Distance from 'a' to 'a' is "<<distance["a"].first<<" and parent is '"<<distance["a"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'b' is "<<distance["b"].first<<" and parent is '"<<distance["b"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'c' is "<<distance["c"].first<<" and parent is '"<<distance["c"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'd' is "<<distance["d"].first<<" and parent is '"<<distance["d"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'e' is "<<distance["e"].first<<" and parent is '"<<distance["e"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'f' is "<<distance["f"].first<<" and parent is '"<<distance["f"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'g' is "<<distance["g"].first<<" and parent is '"<<distance["g"].second;
        std::cout<<"'"<<std::endl;
        std::cout<<"Distance from 'a' to 'h' is "<<distance["h"].first<<" and parent is '"<<distance["h"].second;
        std::cout<<"'"<<std::endl;
        */
        delete temp;
        return 0;

}
