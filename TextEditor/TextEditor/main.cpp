//
//  main.cpp
//  TextEditor
//
//  Created by 유정무 on 2020/12/20.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class TextCreater {
    public :
    TextCreater(){
        std::ofstream on("fout.txt");
        std::ifstream in("test.txt");
        
        if (!in.is_open()) {
            std::cout << "파일을 찾을 수 없습니다!" << std::endl;
        }
        
        char letter;
        std::vector<char> input;
        while(!in.eof()){
            in.get(letter);
            char lettered = (char)letter;
            input.push_back(lettered);
            
            if((int)lettered == 32 || (int)lettered == 46){
                std::string word(input.begin(), input.end());
                createdText.push_back(word);
                word = "";
                input = {};
            }
        }
    }
    
    std::vector<std::string> &getCreatedText(){
        return this->createdText;
    }
    
    int getIndex(){
        return this->index;
    }
    
    void setIndex(int index_){
        this->index = index_;
    }
    
    private :
    std::vector<std::string> createdText;
    int index=0;
    
};

class TextViewer {
    public :
    TextViewer(TextCreater createdText_):createdText(createdText_){
    }
    
    void show(TextCreater createdText){
        //vetor<string>와 현재 index 정보을 받아오고 바이트, 라인의 수를 카운트할 변수 선언
        int word_index = createdText.getIndex();
        int byte_count = 0;
        int line_count = 2;
        
        
        std::cout << " 1|"; //첫번째 줄 출력하기 위한 형식
        //gotText에 저장되있는 단어들을 word_index에 저장된 index부터 하나씩 꺼내옴.
        for(int i=word_index;i < createdText.getCreatedText().size(); i++)
        {
            //단어를 하나씩 꺼내며 index값을 늘려주고 단어당 바이트를 합산한다.
            std::string strd = createdText.getCreatedText().at(i);
            byte_count += strd.length();
            
            //만약 75바이트가 넘어간다면 개행을 하고 출력형식에 맞게 출력을 한다. 개행을 할때 마다 줄의 갯수를 합산한다.
            if(byte_count > 75){
                std::cout << std::endl;
                if(line_count<10){
                    std::cout << " " << line_count << "|";
                }
                else if(line_count<21){
                    std::cout << line_count << "|";
                }
                byte_count = 0;
                byte_count += strd.length();
                line_count ++;
                
                //line수가 20줄을 넘긴다면 index 값을 보정해준 후 createdText의 index값을 갱신해준다. 이후 반복문 탈출
                if(line_count > 21) {
                    break;
                }
            }
            std::cout<<strd;
        }
    }
    
    void showNext(TextCreater createdText){
        //vetor<string>와 현재 index 정보을 받아오고 바이트, 라인의 수를 카운트할 변수 선언
        int word_index = createdText.getIndex();
        int byte_count = 0;
        int line_count = 2;
        
        for(int i=word_index;i < createdText.getCreatedText().size(); i++)
        {
            //단어를 하나씩 꺼내며 index값을 늘려주고 단어당 바이트를 합산한다.
            std::string strd = createdText.getCreatedText().at(i);
            word_index ++;
            byte_count += strd.length();
            
            //만약 75바이트가 넘어간다면 개행을 하고 출력형식에 맞게 출력을 한다. 개행을 할때 마다 줄의 갯수를 합산한다.
            if(byte_count > 75){
                byte_count = 0;
                byte_count += strd.length();
                line_count ++;
                
                //line수가 20줄을 넘긴다면 index 값을 보정해준 후 createdText의 index값을 갱신해준다. 이후 반복문 탈출
                if(line_count > 21) {
                    word_index--;
                    createdText.setIndex(word_index);
                    break;
                }
            }
        }
        show(createdText);
    }
    
    void showPrev(TextCreater createdText){
        //vetor<string>와 현재 index 정보을 받아오고 바이트, 라인의 수를 카운트할 변수 선언
        int word_index = createdText.getIndex();
        int byte_count = 0;
        int line_count = 2;
        
        for(int i=word_index; i >= 0; i--)
        {
            //단어를 하나씩 꺼내며 index값을 늘려주고 단어당 바이트를 합산한다.
            std::string strd = createdText.getCreatedText().at(i);
            word_index --;
            byte_count += strd.length();
            
            //만약 75바이트가 넘어간다면 개행을 하고 출력형식에 맞게 출력을 한다. 개행을 할때 마다 줄의 갯수를 합산한다.
            if(byte_count > 75){
                byte_count = 0;
                byte_count += strd.length();
                line_count ++;
                
                //line수가 20줄을 넘긴다면 index 값을 보정해준 후 createdText의 index값을 갱신해준다. 이후 반복문 탈출
                if(line_count > 21) {
                    createdText.setIndex(word_index);
                    break;
                }
            }
        }
        show(createdText);
    }
    
    TextCreater getTextCreater(){
        return this->createdText;
    }
    
    private :
    TextCreater createdText;
};

class Command{
public:
    virtual void execute(void) = 0;
    virtual ~Command(void){};
};

class Delete : public Command{
public:
    Delete(std::vector<std::string> command, TextCreater createdText_, TextViewer viewer_):createdText(createdText_), viewer(viewer_){
        first = stoi(command[0]);
        second = stoi(command[1]);
        execute();
    }
    void execute(void){
        std::vector<std::string> &gotText = createdText.getCreatedText();
        int word_index = createdText.getIndex();
        int lineindex=1;
        int wordatlineindex = 1;
        int byte_count = 0;
        int mustdeleted = 0;
        std::string message = "삭제 범위가 초과했습니다!";
        bool isDeleted = false;
        
        try{
            for(int i=word_index;i < gotText.size(); i++)
            {
                //단어를 하나씩 꺼내며 index값을 늘려주고 단어당 바이트를 합산한다.
                std::string strd = gotText.at(i);
                word_index ++;
                byte_count += strd.length();
                
                if(lineindex == first){
                    wordatlineindex++;
                    if(wordatlineindex == second){
                        word_index--;
                        mustdeleted = word_index;
                        isDeleted = true;
                    }
                }
                
                if(first>20) throw message;
                
                //만약 75바이트가 넘어간다면 개행을 하고 출력형식에 맞게 출력을 한다. 개행을 할때 마다 줄의 갯수를 합산한다.
                if(byte_count > 75){
                    byte_count = 0;
                    lineindex++;
                    byte_count += strd.length();
                }
            }
            if(!isDeleted) throw message;
            createdText.getCreatedText().erase(createdText.getCreatedText().begin()+mustdeleted);
            viewer.show(createdText);
        }catch(std::string message_){
            std::cout << message_ << std::endl;
        }
    }
private:
    TextCreater createdText;
    TextViewer viewer;
    int first;
    int second;
};

class NextPage : public Command{
public:
    NextPage(TextCreater createdText_, TextViewer viewer_):createdText(createdText_), viewer(viewer_){
        execute();
    }
    void execute(void){
        int firstIndex = createdText.getIndex();
        std::string message = "다음페이지가 없습니다!";
        
        try{
            if(firstIndex == createdText.getCreatedText().size()) throw message;
            viewer.showNext(createdText);
        }catch(std::string message_){
            std::cout << message_ << std::endl;
        }
    }
private:
    TextCreater createdText;
    TextViewer viewer;
};

class PrevPage : public Command{
public:
    PrevPage(TextCreater createdText_, TextViewer viewer_):createdText(createdText_), viewer(viewer_){
        execute();
    }
    void execute(void){
        int firstIndex = createdText.getIndex();
        std::string message = "이전페이지가 없습니다!";
        
        try{
            if(firstIndex == 0 ) throw message;
            viewer.showPrev(createdText);
        }catch(std::string message_){
            std::cout << message_ << std::endl;
        }
    }
private:
    TextCreater createdText;
    TextViewer viewer;
};

class CommandReciver {
    public :
    CommandReciver(TextCreater createdText_, TextViewer viewer_): createdText(createdText_), viewer(viewer_){
        while(1){
            printDashLine();
            std::cout << "n: 다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t: 저장후종료" << std::endl;
            printDashLine();
            std::cout << "(콘솔페이지)" << std::endl;
            printDashLine();
            std::cout << "입력: ";
            getCommand();
        }
    }
    
    void printDashLine(){
        int i = 0;
        for(i=0; i<75; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }
    
    std::vector<std::string> get_cmdlist(std::string str){
        std::istringstream ss(str);
        std::string stringBuffer;
        std::vector<std::string> list;
        list.clear();
        while (getline(ss, stringBuffer, ',')){
            list.push_back(stringBuffer);
        }
        return list;
    }
    
    void getCommand(){
        try{
            std::string command;
            std::cin >> command;
            std::string inn_command;
            char f_letter;
            std::vector<std::string> sp_command;
            
            f_letter = command.at(0);
            
            std::cout << inn_command << std::endl;
            if(f_letter == 'i'){
                inn_command = command.substr(2,command.length()-3);
                std::cout << "inserting";
                std::cout << std::endl;
                sp_command = get_cmdlist(inn_command);
                std::cout << sp_command[0];
            }
            else if(f_letter == 'd'){
                inn_command = command.substr(2,command.length()-3);
                sp_command = get_cmdlist(inn_command);
                Delete del(sp_command,createdText,viewer);
            }
            else if(f_letter == 's'){
                inn_command = command.substr(2,command.length()-3);
                std::cout << std::endl;
                sp_command = get_cmdlist(inn_command);
                std::cout << sp_command[0];
            }
            else if(f_letter == 'c'){
                inn_command = command.substr(2,command.length()-3);
                std::cout << "search";
                std::cout << std::endl;
                sp_command = get_cmdlist(inn_command);
                std::cout << sp_command[0];
            }
            else if(f_letter == 't'){
                std::cout << "search";
                std::cout << std::endl;
                std::cout << sp_command[0];
            }
            else if(f_letter == 'n'){
                NextPage next(createdText,viewer);
            }
            else if(f_letter == 'p'){
                std::cout << "search";
                std::cout << std::endl;
                PrevPage prev(createdText,viewer);
            }
            
        }catch(std::out_of_range){
            std::cout << "잘못된 입력 - 다시 입력" << std::endl;
            std::cout << "입력: " << std::endl;
            getCommand();
        }
    }
    
private:
    TextCreater createdText;
    TextViewer viewer;
};



int main(int argc, const char * argv[]) {
    TextCreater createdText;
    TextViewer viewer(createdText);
    viewer.show(createdText);
    CommandReciver command_reciver(createdText, viewer);
    std::cout<<std::endl;
    std::cout <<std::endl;
}

