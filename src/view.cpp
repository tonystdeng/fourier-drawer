#include "view.hpp"


bool checkClose (sf::Event,sf::RenderWindow*);

Game::Game(std::string path)
{
    getLine(path);
    window=new sf::RenderWindow(sf::VideoMode({width,height}),"fps: ");
    window->setFramerateLimit(60);
}


void Game::updateLines()// function copied from privous project
{
    for (int j=0;j<lineNum.size();j++){
        for (int i=0;i<lineNum[j];i++){
            sf::Vector2f pre=lines[j][i].position;
            double *angle=&angles[j][i],length=lengthes[j][i];
            *angle=std::fmod(*angle,2*M_PI) ;
            sf::Vector2f newpos(pre.x+std::cos(*angle)*length,pre.y+std::sin(*angle)*length);
            lines[j][i+1].position=newpos;
            *angle-=dps[j][i];
        }record[j].append(lines[j][lineNum[j]]);
        record[j][record[j].getVertexCount()-1].color={0,255,255};
    }
}

void Game::getLine(std::string path)// function copied from previous code, removed a large part
{
    angles.clear();lengthes.clear();dps.clear();lines.clear();record.clear();

    lineinfo filereturn=fileLoader(path,angles);
    double biggestLen=-INFINITY;std::vector<double> lineSum;
    for (int j=0;j<filereturn.size();j++){
        // avoid segmentation fault
        lengthes.push_back(std::vector<double>());
        dps.push_back(std::vector<double>());
        lines.push_back(sf::VertexArray(sf::PrimitiveType::LineStrip));
        record.push_back(sf::VertexArray(sf::PrimitiveType::LineStrip));
        lineNum.push_back(0);
        // end^
        std::vector<al> circles=filereturn[j].first;
        lineNum[j]=filereturn[j].second;
        //std::cout<<filereturn[j].second<<" "<<filereturn[j].first.size()<<"\n";
        int index=0;
        lineSum.push_back(0);
        for (al i:circles){
            float length=i.first;
            float angle=i.second;
            lineSum[j]+=std::abs(length);
            lengthes[j].push_back(length);
            dps[j].push_back(angle);
            //std::cout<<length<<" "<<angle<<" "<<angles[j][index]<<"\n";
            index++;
        }biggestLen=biggestLen<lineSum[j]?lineSum[j]:biggestLen;
    }
    //below is formating the angel, add length to totle length, then add them both to the list, 
    // starting a new loop cus need to get the biggest length
    for (int j=0;j<filereturn.size();j++){
        double scale=hw/biggestLen;lineSum[j]*=scale;
        //std::cout<<biggestLen;
        sf::Vertex origin{{hw,hh}};
        unsigned char color=255/filereturn.size()*(j+1);
        origin.color={255,color,color};
        lines[j].append(origin);
        std::reverse(lengthes[j].begin(),lengthes[j].end());
        for (int i=0;i<lengthes[j].size();i++)
        {
            sf::Vertex newPtr;newPtr.color={255,color,color};
            lines[j].append(newPtr);
            lengthes[j][i]*=scale;lineSum[j]-=lengthes[j][i];
        }
        float angleSum=0;for (float i:dps[j]){angleSum+=std::abs(i);}
        //std::cout<<scale<<" ";
        if (angleSum){
            scale=0.08/(angleSum/dps[j].size());
            // looking back at jan 3 25, all this data is none sense, glad i don't really need it anyway
            // update: jan 10, now i needs to, and i optimized it lol
            for (double &i:dps[j]){i*=scale;}
        }
        std::reverse(lengthes[j].begin(),lengthes[j].end());
    }
}

Game::~Game()
{
    delete window;
}

void Game::main()// function copied from privous project
{

    if (checkEvent()){return;}
    updatefps();
    window->clear(sf::Color::Black);
    updateLines();
    for (int i=0;i<lines.size();i++)
    {
        if (showCircles){
            drawCircles(lines[i],255/lines.size()*(i+1));
        }
        window->draw(lines[i]);
        window->draw(record[i]);
    }
    window->display();
}

void Game::drawCircles(sf::VertexArray lines,unsigned char color)
{
    sf::Vector2f mid=lines[0].position;
    for (int i=1;i<lines.getVertexCount();i++)
    {
        sf::Vector2f end=lines[i].position;
        float radius=std::sqrt((mid.x-end.x)*(mid.x-end.x)+(mid.y-end.y)*(mid.y-end.y));
        sf::Vector2f pos(mid.x-radius,mid.y-radius);
        sf::CircleShape circle;
        circle.setRadius(radius);
        circle.setPosition(pos);
        circle.setFillColor({0,0,0,0});
        circle.setOutlineThickness(0.5);
        circle.setOutlineColor({255,color,color});
        window->draw(circle);
        mid=end;
    }
}


void Game::updatefps()
{
    elapsed=clock.restart();
    fpsupdateCountdown+=elapsed;
    if (fpsupdateCountdown>fpsupdateInterval)
    {
        fps = 1./elapsed.asSeconds();
        fpsloader<<fps;
        window->setTitle("fps: "+fpsloader.str());
        fpsloader.str("");fpsloader.clear();
        fpsupdateCountdown-=fpsupdateInterval;
    }
}



lineinfo fileLoader(std::string path,std::vector<std::vector<double>>& angles){//function copied from previous code
    lineinfo returns;
    std::vector<al> circles;// first: length, second: dps
    std::ifstream lineSet(path);
    if (!lineSet){std::cout<<"error file not found\n";std::exit(1);}
    std::string line;//temp var storing one line of float in string form, refreshin eash loop
    int lineNum=0,lineNum1=0;
    angles.push_back(std::vector<double>());
    while(std::getline(lineSet,line)){//get the line and check if it's the end
        if (line=="z"){
            returns.push_back(std::make_pair(circles,(lineNum+1)/3));
            circles.clear();lineNum=0;lineNum1++;
            angles.push_back(std::vector<double>());
            continue;
        }
        float num=std::stof(line);
        //std::cout<<num<<" "<<lineNum<<"\n";
        switch (lineNum%3){
        case 0:
            angles[lineNum1].push_back(2*M_PI-num);
            break;// Designing a user interfac
        case 1:// angle
            circles.push_back(al());
            circles[lineNum/3].first=num;
            break;
        
        case 2:// length
            circles[(lineNum-1)/3].second=num;
            break;
        }
        lineNum++;
    }
    lineSet.close();
    return returns;
}// return=[[[angle, length]...],numofline(single int)]

bool Game::checkEvent ()
{
    while (const std::optional event = window->pollEvent()){
        if (event->getIf<sf::Event::Closed>()){
            window->close();
            return true;}
        if (const auto * key=event->getIf<sf::Event::KeyPressed>()){
            if (key->code==sf::Keyboard::Key::C){
                showCircles=1-showCircles;
            }else if (key->code==sf::Keyboard::Key::P){
                window->clear(sf::Color::Black);
                for (int i=0;i<lines.size();i++){
                    window->draw(record[i]);
                }
                window->display();
                while(1){
                    while (const std::optional event = window->pollEvent()){
                        if (event->is<sf::Event::Closed>()){
                            window->close();
                            return true;
                        }
                        else if (event->getIf<sf::Event::KeyPressed>()){
                            if (key->code==sf::Keyboard::Key::P) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }return false;
}