#include <iostream>
#include<cstdlib>
using namespace std;
struct Node{
	int data;
	Node* next;
};
class LinkedList{
	int size;
	Node *head;
	Node *tail;
public:
	LinkedList(){
		size = 0;
		head = nullptr;
		tail = nullptr;
	}
	void add(int data){
        Node *node = new Node{data, nullptr};
		if(!head){
			head = node;
			tail = node;
		} else{
			tail->next = node;
			tail = node;
		}
		size++;
	}
	
	void addLast(int num){
		add(num);
	}

	void addFirst(int num){
		if(!head){
			add(num);
			return;
		}
		Node* node = new Node{num, head};
		head = node;
		size++;
	}

	int removeFirst(){
		if(size == 0){
			return -1;
		}
		int tempInt = head->data;
		Node* temp = head;
		head = head->next;
		free(temp);
		size--;
		return tempInt;
	}
	int get(int position){
		if(size == 0){
            return -1;
        }
		Node* curr = head;
        int a = 1;
        while(a != position){
            curr = curr->next;
            a++;
        }
		return curr->data;
	}
    int removeLast(){
        if(size == 0){
            return -1;
        }
        Node* curr = head;
        while(curr->next != tail && curr != tail){
            curr = curr->next;
        }
        int out = tail->data;
        delete tail;
        tail = curr;
        tail->next = nullptr;
        size--;
        return out;
    }
	int _size(){
		return size;
	}

	void print(){
		Node *p = head;
		while(p){
			cout << p->data << "->";
			p = p->next;
		}
		cout << endl;
		free(p);
	}
};

class Deque{
	LinkedList* list;
public:
	Deque(){
		list = new LinkedList();
	}
	void push_front(int num){
		list->addFirst(num);
	}
    void push_back(int num){
        list->addLast(num);
    }
	int pop_front(){
		return list->removeFirst();
	}
	int pop_back(){
		return list->removeLast();
	}
    int peek_front(){
        return list->get(1);
    }
    int peek_back(){
        return list->get(size());
    }
	int size() {
		return list->_size();
	}
	bool isEmpty() {
		return size() == 0;
	}
	void print() {
		list->print();
	}
};

int main(){
	Deque* deque = new Deque();
    char op;
    int num;
    while(true){
        cout << "Enter operation: ";
        cin >> op;
        switch(op){
            case 'e':
                cin >> num;
                deque->push_front(num);
                break;
            case 'E':
                cin >> num;
                deque->push_back(num);
                break;
            case 'p':
                cout << (deque->isEmpty()? "Queue is empty!\n" : "Front of the queue is " + to_string(deque->peek_front()) + "\n");
                break;
            case 'P':
                cout << (deque->isEmpty()? "Queue is empty!\n" : "Back of the queue is " + to_string(deque->peek_back()) + "\n");
                break;
            case 'd':
                cout << "Removed number at front: " << deque->pop_front() << endl;
                break;
            case 'D':
                cout << "Removed number at back: " << deque->pop_back() << endl;
                break;
            case 'S':
                cout << "Size: " << deque->size() << endl;
                break;
            case '@':
                deque->print();
                break;
        }
        if(op == 'x' || op == 'X'){
            cout << "Exiting";
            break;
        }
    }
    return 0;
}