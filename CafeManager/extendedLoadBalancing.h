#pragma once
#include <iostream>
using namespace std;

class Reader {
public:
	virtual void read() {
		cout << "read something" << endl;
		readData();
		readCondition();
	}
protected:
	void readData() { cout << "read something data" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class Writer {
public:
	virtual void write() {
		cout << "write something" << endl;
		writeData();
		writeResult();
	}
protected:
	void writeData() { cout << "write something Data" << endl; }
	void writeResult() { cout << "write something Result" << endl; }
};

class Computer {
public:
	virtual void compute() { cout << "compute something" << endl; }
private:

};

// Reader �����ؼ� ���ϴµ��� ���� ���� �ε� �뷱�̿��� Reader �޾Ƽ� read��
class ReaderSample : virtual public Reader {
public:
	void read() {
		cout << "Reader Sample" << endl;
		readCondition();
		readData();
	}
	void readData() { cout << "Read Data Sample" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class WriterSample : virtual public Writer {
public:
	void write() {
		cout << "Writer Sample" << endl;
		this->writeData(); // Ȥ�� �θ� ��������� 
		this->writeResult();
	}
private:
};

class ExtendedLoadBalancing {
public:
	Reader* reader;
	Writer* writer;
	Computer* computer;
public:
	ExtendedLoadBalancing() {
		reader = new Reader;
		writer = new Writer;
		computer = new Computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader) {
		this->reader = reader;
		init();
	}
	ExtendedLoadBalancing(Writer* writer) {
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Computer* computer) {
		this->computer = computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer)
	{
		this->reader = reader;
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer, Computer* computer) {
		this->reader = reader;
		this->writer = writer;
		this->computer = computer;
		init();
	}

	void init() {
		reader->read();
		computer->compute();
		writer->write();
	}
};

extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

extern void load();
extern void test();

// Basic �ܰ� ���� �ð� ���� ���� �� �ε�뷱�� 
// ���� �ð� �� �ٸ� ���� �߰��� ���� �ε� �뷱�̵� ����� ���� ���� 
// ���Ѵٸ� ����� ���� Ȯ����� ������ �� �ְ� �ϱ⸦ ��ǥ�� �ϰ�����

class BasicReader : virtual public Reader {
public:
	void read() {
		load();
	}
};

class BasicComputer : virtual public Computer {
private:

public:
	void compute() {
		loadBalancing();
	}

	void loadBalancing() {
		while (!isEmptyOrder()) {
			order curOrd = selectOrder();
			for (int i = 0; i < curOrd.getNumOfDrink(); i++)
				distributeOrder(selectBarista());
		}
	}

	bool isEmptyOrder() {
		return ord.empty();
	}

	order selectOrder() {
		return ord.front();
	}

	void distributeOrder(int selected) {
		bari[selected].incNumOfCofMade();
		ord.pop();
	}

	int selectBarista() {
		int min = 1000;
		barista curBari;
		int bariId;
		for (int i = 0; i < bari.size(); i++)
			if (min > bari[i].getNumOfCofMade())
			{
				min = bari[i].getNumOfCofMade();
				curBari = bari[i];
				bariId = i;
			}
		return bariId;
	}

};

class BasicWriter : virtual public Writer {
public:
	void write() {
		test();
	}
};