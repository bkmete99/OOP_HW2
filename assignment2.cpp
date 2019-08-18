#include <iostream>

#define MAX_OPERATOR_SIZE 15
using namespace std;

int id_global=0;

class Operator{

    int center_x;
    int center_y;
    int op_size;

public:
    Operator(){};
    Operator(int x, int y, int size);
    void reset(int new_x, int new_y, int new_size){center_x=new_x;center_y=new_y;op_size=new_size;};


    void set_x(int new_x){center_x=new_x;};
    int get_x() {return center_x;}

    void set_y(int new_y){center_y=new_y;};;
    int get_y() {return center_y;};

    void set_size( int new_size ){op_size=new_size;};
    int get_size(){return op_size;};

};


Operator::Operator(int x, int y, int size) {
    set_x(x);
    set_y(y);
    set_size(size);
}


class ArithmeticOperator: public Operator{

    char sign;
    int id;

public:

    ArithmeticOperator(int x, int y, int size, char sign);
    char get_sign() {return sign;}
// Prints out operator's center location, size, and sign character
    int get_id();
    void set_id(int input_id){id=input_id;}
    void print_operator();

};

ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign) {


    ArithmeticOperator::sign = sign;
    if(get_sign()!='+' && get_sign()!='-' && get_sign()!='x' &&get_sign()!='/'){
        print_operator();
        return;
    }else {
        set_x(x);
        set_y(y);
        set_size(size);
        ArithmeticOperator::sign = sign;
    }

}

void ArithmeticOperator::print_operator() {
    if(get_sign()=='+'|| get_sign()=='x' ||get_sign()=='/'|| get_sign()=='-'){
        cout<<"ARITHMETIC_OPERATOR["<<get_sign()<<"], CENTER_LOCATION["<<get_x();
        cout<<","<<get_y()<<"], SIZE["<<get_size()<<"]"<<endl;}
    else{cout<<"SIGN parameter is invalid!"<<endl;}

}

int ArithmeticOperator::get_id() {
    return id;
}


class OperatorGrid{

    int grid_rows;
    int grid_cols;
    char **grid;
    int **idofoperators;
    int **idofcenters;
    int num_operators;
    ArithmeticOperator *operators[MAX_OPERATOR_SIZE];

public:
    OperatorGrid(int rows, int cols);
    ~OperatorGrid();
    void carray(){for(int i=0;i<MAX_OPERATOR_SIZE;i++){
        operators[i]=NULL;}}
    bool place_operator (ArithmeticOperator *);
    bool move_operator (int x, int y, char direction, int move_by);
    void print_operators();
    //void change

};

OperatorGrid::OperatorGrid(int rows, int cols) {
    grid_rows=rows;
    grid_cols=cols;
    grid=new char*[grid_rows];
    idofoperators=new int*[grid_rows];
    idofcenters=new int*[grid_rows];
    for(int i=0; i<rows; ++i) {
        grid[i]=new char[cols];}
    for(int i=0; i<rows; ++i) {
        idofcenters[i]=new int[cols];}
    for(int i=0; i<rows; ++i) {
        idofoperators[i]=new int[cols];}
    //Created 2 dimensional grid !

    for(int j=0; j<rows; j++)
    {for(int i=0; i<cols; i++)
        {grid[j][i]='.';}}
    for(int j=0; j<rows; j++)
    {for(int i=0; i<cols; i++)
        {idofcenters[j][i]=-1;}}
    for(int j=0; j<rows; j++)
    {for(int i=0; i<cols; i++)
        {idofoperators[j][i]=-1;}}
carray();
}

OperatorGrid::~OperatorGrid() {
    for(int i=0; i<grid_rows; i++){delete grid[i];}
    delete *grid;
    for(int i=0; i<grid_rows; i++){delete idofoperators[i];}
    delete *idofoperators;
    for(int i=0; i<grid_rows; i++){delete idofcenters[i];}
    delete *idofcenters;
    for(int i=0;i<num_operators;i++){delete operators[i];}

    delete *operators;
    cout<<"DESTRUCTOR: GIVE BACK["<<grid_rows<<","<<grid_cols<<"] chars"<<endl;
    cout<<"DESTRUCTOR: GIVE BACK["<<num_operators<<"] operators"<<endl;
}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by) {
    int operand_id=idofoperators[x-1][y-1];
    int init_center_x=-1,init_center_y=-1;
    for(int j=0; j<grid_rows; j++)
    {for(int i=0; i<grid_cols; i++)
        {
            if(operand_id==idofcenters[j][i]){init_center_x=j;init_center_y=i;break;}
        }
    }
    int total_id=0;
    for(int j=0; j<grid_rows; j++)
    {for(int i=0; i<grid_cols; i++)
        {
            if(operand_id==idofoperators[j][i]){total_id++;}
        }
    }
    char operand_sign=grid[init_center_x][init_center_y];
    int op_size;
    if(operand_sign=='+' || operand_sign=='x'){op_size=(total_id-1)/4;}
    if(operand_sign=='-' || operand_sign=='/'){op_size=(total_id-1)/2;}


    int x_after=init_center_x,y_after=init_center_y;
    if(direction=='U'){x_after=x_after-move_by;}
    if(direction=='D'){x_after=x_after+move_by;}
    if(direction=='R'){y_after=y_after+move_by;}
    if(direction=='L'){y_after=y_after-move_by;}
//ArithmeticOperator opptr(x_after,y_after,op_size,operand_sign);
    //opptr.set_id(operand_id);


    //if sign +
    int yco=y_after,xco=x_after,size=op_size;
    bool issuccess=true,isconflict=false;
    if(operand_sign=='+'){
        //Control part for border or conflict errors.
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            //cout<<"BORDER ERROR: Operator "<<operand_sign<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
            cout<<"BORDER ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
            cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;

            issuccess=false;
        }
        for(int i=yco-size;i<=yco+size;i++){if(i<0 || i>=grid_cols)continue;
            if(idofoperators[xco][i]!=operand_id && idofoperators[xco][i]!=-1 && !isconflict){
                //cout<<"CONFLICT ERROR: Operator "<<operand_sign<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;}
        }
        for(int i=xco-size;i<=xco+size;i++){if(i<0 || i>=grid_rows)continue;
            if(idofoperators[i][yco]!=operand_id && idofoperators[i][yco]!=-1&& !isconflict){
                //cout<<"CONFLICT ERROR: Operator "<<operand_sign<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        //Insertion Part
        if(!issuccess)return false;

        //if we came here,there is no error
        //firstly we should delete old data
        //DELETE PART !
        yco=init_center_y;xco=init_center_x;
        for (int i = yco - size; i <= yco + size; i++) {
            grid[xco][i] = '.';
            idofoperators[xco][i] = -1;

        }
        for (int j = xco - size; j <= xco + size; j++) {
            grid[j][yco] = '.';
            idofoperators[j][yco] = -1;
        }
        idofcenters[init_center_x][init_center_y]=-1;
        idofcenters[x_after][y_after]=operand_id;

        //Thus we delete old data we can insert moved operator !
        //              INSERT AGAIN!
        yco=y_after;xco=x_after;
        for (int i = yco - size; i <= yco + size; i++) {
            grid[xco][i] = '+';
            idofoperators[xco][i] = operand_id;

        }
        for (int j = xco - size; j <= xco + size; j++) {
            grid[j][yco] = '+';
            idofoperators[j][yco] = operand_id;
        }
//Change operators arrays numbers
        operators[operand_id]->reset(xco+1,yco+1,size);

    }


isconflict=false;

    //if sign -
    if(operand_sign=='-'){
        if(yco-size<0 ||yco+size>=grid_cols ||x_after>=grid_rows || x_after<0 ){
            cout<<"BORDER ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
            cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
            issuccess=false;
        }
        for(int i=yco-size;i<=yco+size;i++){if((i<0 || i>=grid_cols ||xco<0 ||xco>=grid_rows)&& !isconflict )continue;
            if(grid[xco][i]!='.' && grid[xco][i]!='-'){
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        if(!issuccess)return false;

        yco=init_center_y;xco=init_center_x;
        //Again we delete old part
        //              DELETE PART
        for(int i=yco-size;i<=yco+size;i++){if(i<0 || i>=grid_cols)continue;
            grid[xco][i]='.';
            idofoperators[xco][i]=-1;
        }
        idofcenters[init_center_x][init_center_y]=-1;
        idofcenters[x_after][y_after]=operand_id;


        //INSERT PART
        yco=y_after;xco=x_after;
        for(int i=yco-size;i<=yco+size;i++){if(i<0 || i>=grid_cols)continue;
            grid[xco][i]='-';
            idofoperators[xco][i]=operand_id;
        }

        operators[operand_id]->reset(xco+1,yco+1,size);
    }


    //if sign x
    if(operand_sign=='x'){
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            cout<<"BORDER ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
            cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
            issuccess=false;
        }
        int j=xco-size;
        for(int i=yco-size;i<=yco+size;i++,j++){
            if(i<0 || i>=grid_cols)continue;//hERE  || i<grid_cols WAS THERE
            if(idofoperators[j][i]!=operand_id && !isconflict && idofoperators[j][i]!=-1){
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){if(i<0 || i>=grid_rows)continue;//HERE || i<grid_rows WAS THERE
            if(idofoperators[j][i]!=operand_id && idofoperators[j][i]!=-1 && !isconflict){
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }

        if(!issuccess)return false;
        //Delete old part
        yco=init_center_y;xco=init_center_x;
        j=xco-size;
        for(int i=yco-size;i<=yco+size;i++,j++){
            grid[j][i]='.';
            idofoperators[j][i]=-1;
        }
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            grid[j][i]='.';
            idofoperators[j][i]=-1;
        }

        idofcenters[init_center_x][init_center_y]=-1;
        idofcenters[x_after][y_after]=operand_id;


        //INSERT PART
        yco=y_after;xco=x_after;

        j=xco-size;
        for(int i=yco-size;i<=yco+size;i++,j++){
            grid[j][i]='x';
            idofoperators[j][i]=operand_id;
        }
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            grid[j][i]='x';
            idofoperators[j][i]=operand_id;
        }


        operators[operand_id]->reset(xco+1,yco+1,size);

    }


    //if sign /
    if(operand_sign=='/'){
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            cout<<"BORDER ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
            cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
            issuccess=false;

        }
        int j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            if(i<0 || i>=grid_cols ||j<0 || j>=grid_rows ||isconflict)continue;
            if(grid[j][i]!='.' && grid[j][i]!='/'){
                cout<<"CONFLICT ERROR: "<<operand_sign<<" can not be moved from ("<<init_center_x+1;
                cout<<","<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        if(!issuccess){return false;}

        //Delete old part
        yco=init_center_y;xco=init_center_x;
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            if(i<0 || i>=grid_cols ||j<0 || j>=grid_rows)continue;
            grid[j][i]='.';
            idofoperators[j][i]=-1;
        }

        idofcenters[init_center_x][init_center_y]=-1;
        idofcenters[x_after][y_after]=operand_id;


        //INSERT PART
        yco=y_after;xco=x_after;
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            if(i<0 || i>=grid_cols ||j<0 || j>=grid_rows)continue;
            grid[j][i]='/';
            idofoperators[j][i]=operand_id;
        }

        operators[operand_id]->reset(xco+1,yco+1,size);
    }
    if(!issuccess){return false;}//there is at least 1 error !



    cout<<"SUCCESS: "<<operand_sign<<" moved from ("<<init_center_x+1<<",";
    cout<<init_center_y+1<<") to ("<<x_after+1<<","<<y_after+1<<")"<<endl;
    return true;

    //return false;
}

void OperatorGrid::print_operators() {
    int i=0;
    while(operators[i]!=NULL){
        operators[i]->print_operator();
        i++;
    }
}

bool OperatorGrid::place_operator(ArithmeticOperator *opptr) {
    if(opptr->get_sign()!='+' &&opptr->get_sign()!='-' &&opptr->get_sign()!='x' &&opptr->get_sign()!='/')return false;
    int xco=opptr->get_x()-1;
    int yco=opptr->get_y()-1;
    int size=opptr->get_size();
    bool issuccess=true,isconflict=false;

    //if sign +
    if(opptr->get_sign()=='+'){
        //Control part for border or conflict errors.
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            cout<<"BORDER ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
            issuccess=false;
        }
        for(int i=yco-size;i<=yco+size;i++){if(i<0 || i>=grid_cols){continue;}
            if(grid[xco][i]!='.' && !isconflict){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;

                issuccess=false;isconflict=true;}
        }
        for(int i=xco-size;i<=xco+size;i++){if(i<0 || i>=grid_rows)continue;
            if(grid[i][yco]!='.' &&!isconflict){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        //Insertion Part
        if(!issuccess)return false;
        opptr->set_id(::id_global);

        for (int i = yco - size; i <= yco + size; i++) {
            grid[xco][i] = '+';
            idofoperators[xco][i] = opptr->get_id();

        }
        for (int j = xco - size; j <= xco + size; j++) {
            grid[j][yco] = '+';
            idofoperators[j][yco] = opptr->get_id();
        }
    }


    //if sign -
    if(opptr->get_sign()=='-'){
        if(yco-size<0 ||yco+size>=grid_cols ||xco>=grid_rows || xco<0){
            cout<<"BORDER ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
            issuccess=false;
        }
        for(int i=yco-size;i<=yco+size;i++){if(i<0 || i>=grid_cols)continue;
            if((grid[xco][i]!='.' ) && !isconflict ){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        if(!issuccess)return false;
        opptr->set_id(::id_global);
        for(int i=yco-size;i<=yco+size;i++){//if(i>=0 || i<grid_cols)continue;
            grid[xco][i]='-';
            idofoperators[xco][i]=opptr->get_id();
        }
    }


    //if sign x
    if(opptr->get_sign()=='x'){
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            cout<<"BORDER ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
            issuccess=false;
        }
        int j=xco-size;
        for(int i=yco-size;i<=yco+size;i++,j++){if(i<0 ||i>=grid_cols ||j>=grid_rows||j<0 )continue;//||i<grid_cols
            if(grid[j][i]!='.' && !isconflict){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){if(i<0 || i>=grid_rows||j>=grid_rows||j<0)continue;
            if(grid[j][i]!='.' && !isconflict){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        //Insert part
        if(!issuccess)return false;

        opptr->set_id(::id_global);
        j=xco-size;
        for(int i=yco-size;i<=yco+size;i++,j++){
            grid[j][i]='x';
            idofoperators[j][i]=opptr->get_id();
        }
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            grid[j][i]='x';
            idofoperators[j][i]=opptr->get_id();
        }

    }


    //if sign /
    if(opptr->get_sign()=='/'){
        if(yco-size<0 ||yco+size>=grid_cols || xco-size<0 || xco+size>=grid_rows){
            cout<<"BORDER ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
            issuccess=false;

        }
        int j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            if(i<0 || i>=grid_cols ||j<0 || j>=grid_rows ||isconflict)continue;
            if(grid[j][i]!='.'){
                cout<<"CONFLICT ERROR: Operator "<<opptr->get_sign()<<" with size "<<size<<" can not be placed on ("<<opptr->get_x()<<","<<opptr->get_y()<<")."<<endl;
                issuccess=false;isconflict=true;
            }
        }
        if(!issuccess){return false;}
        opptr->set_id(::id_global);
        j=xco+size;
        for(int i=yco-size;i<=yco+size;i++,j--){
            if(i<0 || i>=grid_cols ||j<0 || j>=grid_rows)continue;
            grid[j][i]='/';
            idofoperators[j][i]=opptr->get_id();
        }
    }
    if(!issuccess){return false;}//there is at least 1 error !

    opptr->set_id(::id_global);
    idofcenters[xco][yco]=opptr->get_id();
    operators[opptr->get_id()]=opptr;
    num_operators=opptr->get_id()+1;
    ::id_global++;
    cout<<"SUCCESS: Operator "<<opptr->get_sign()<<" with size ";
    cout<<opptr->get_size()<<" is placed on ("<<opptr->get_x()<<",";
    cout<<opptr->get_y()<<")."<<endl;

    return true;
}


