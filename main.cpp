#include <iostream>

using namespace std;

struct Node{
    int data;
    int LThread,RThread;
    Node *Left,*Right;
    Node (int Data)
    {
        data=Data;
    }
};

Node *root;
Node *current;
Node *ptrDelete;

bool directionLeft=false;
bool directionRight=false;

void insertData(int data)
{
    Node *node=new Node(data);
    if(root->Left==root&&root->Right==root){
        node->LThread=root->LThread;
        node->Left=root->Left;
        node->Right=root->Right;
        root->Left=node;
        root->LThread=1;
        node->RThread=0;
    }
    else{
        current=root->Left;
        while(true){
            if(node->data < current->data){
                if(current->LThread==0){
                    directionLeft=true;
                    directionRight=false;
                    break;
                }
                else{
                    current=current->Left;
                }
            }
            else if(node->data > current->data){
                if(current->RThread==0){
                    directionLeft=false;
                    directionRight=true;
                    break;
                }
                else{
                    current=current->Right;
                }
            }
            else return;
        }
        if(directionLeft){
            node->LThread=current->LThread;
            node->Left=current->Left;
            current->Left=node;
            current->LThread=1;
            node->RThread=0;
            node->Right=current;
        }
        else if(directionRight){
            node->RThread=current->RThread;
            node->Right=current->Right;
            current->Right=node;
            current->RThread=1;
            node->LThread=0;
            node->Left=current;
        }
        else ;
    }
}

//--------------------------------------------------------------------------- forward

Node *nextForward(Node *root)
{
    if(root->RThread==0) return root->Right;
    root=root->Right;
    while(root->LThread==1){
        root=root->Left;
    }
    return root;

}
void inOrderForward()
{
    current=root->Left;
    while(current->LThread==1){
        current=current->Left;
    }
    while(current!=root){
        cout<<current->data<<" ";
        current=nextForward(current);
    }
}

//----------------------------------------------------------------------------- backward

Node *nextBackward(Node *root)
{
    if(root->LThread==0) return root->Left;
    root=root->Left;
    while(root->RThread==1){
        root=root->Right;
    }
    return root;
}

void inOrderBackward()
{
    current=root->Left;
    while(current->RThread==1){
        current=current->Right;
    }
    while(current!=root){
        cout<<current->data<<" ";
        current=nextBackward(current);
    }
}
//---------------------------------------------------------------------------------

int serchMax(Node *node)
{
    while(node->RThread==1){
        node=node->Right;
    }
    return node->data;
}

void deleteData(int data)
{
    current=root->Left;
    while(current->LThread==1){
        current=current->Left;
    }
    while(current!=root){
        if(current->data==data){
            ptrDelete=current;
            if(current->LThread==1&&current->RThread==0){
                Node *ptr=current->Left;
                while(ptr->RThread==1){
                    ptr=ptr->Right;
                }
                ptr->Right=current->Right;
                current=current->Left;
                delete ptrDelete;
                break;
            }
            else if(current->LThread==0&&current->RThread==1){
                Node *ptr=current->Right;
                while(ptr->LThread==1){
                    ptr=ptr->Left;
                }
                ptr->Left=current->Left;
                current=current->Right;
                delete ptrDelete;
                break;
            }
            else if(current->LThread==0&&current->RThread==0){
                if(current->Right->Left==current){
                    current->Right->LThread=current->LThread;
                    current=current->Left;
                    delete ptrDelete;
                    break;
                }
                else{
                    current->Left->RThread=current->RThread;
                    current=current->Right;
                    delete ptrDelete;
                    break;
                }
            }
            else {//(current->LThread==1&&current->RThread==1){
                int numMax=serchMax(current->Left);
                deleteData(numMax);
                current->data=numMax;
                break;
            }
        }
        current=nextForward(current);
        if(current==root) cout<<"\nNOT FOUND !!!"<<endl;
    }

}
int main()
{
    root=new Node(999);
    root->Left=root->Right=root;
    root->LThread=0;
    root->RThread=1;

    int num,numD;
    for(int i=1;i<5;i++){
        cout<<"Insert : ";
        cin>>num;
        insertData(num);
    }
    inOrderForward();
    cout<<endl;
    inOrderBackward();
    cout<<"\nDetele : ";
    cin>>numD;
    deleteData(numD);
    cout<<endl;
    inOrderBackward();

    return 0;
}
