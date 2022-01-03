#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<iterator>


//la hrana am creat hrane diferite si nu e bine tre sa vad cum fac cu mapul ala

using namespace std;

class CitireAfisare
{
public:
	virtual istream& citire(istream&) = 0;
	virtual ostream& afisare(ostream&) const = 0;
};

class ExceptiePretHrana :public exception
{
public:
	virtual const char* what() const throw() {

		return "Pretul ar trebui sa fie mai mare decat 0. Va rugam introduceti din nou :";
	}
}exceptiePretHrana;

class ExceptieTipAnimal :public exception
{
public:
	virtual const char* what() const throw() {

		return "Hrana este disponibila doar pentru pisici sau caini. Va rugam introduceti din nou :";
	}
}exceptieTipAnimal;


class Hrana
{
	protected:
		string nume;
		double pret;
		string tipAnimal;
		bool estePtProblemeSpeciale;

	public:
		//setters
		void setNume(string nume) { this->nume = nume; }
		void setPret(double pret) { this->pret = pret; }
		void setTipAnimal(string tipAnimal) { this->tipAnimal = tipAnimal; }
		void setEstePtProblemeSpeciale(bool estePtProblemeSpeciale) { this->estePtProblemeSpeciale = estePtProblemeSpeciale; }

		//getters
		string getNume() { return this->nume; }
		double getPret() { return this->pret; }
		string getTipAnimal() { return this->tipAnimal; }
		bool getEstePtProblemeSpeciale() { return this->estePtProblemeSpeciale; }

		//constructor fara parametrii
		Hrana();

		//constructor cu toti parametrii
		Hrana(string nume, double pret, string tipAnimal, bool areProblemeSpeciale);

		//copy constructor
		Hrana(const Hrana& other);

		//overload operator=
		Hrana& operator=(const Hrana& other);

		//afisare 
		virtual ostream& afisare(ostream& out) const;

		//citire
		virtual istream& citire(istream& in);

		//overload operator<<
		friend ostream& operator<<(ostream& out, const Hrana& h);

		//overload operator>>
		friend istream& operator>>(istream& in, Hrana& h);

		//destructor
		~Hrana();

		//function
		double calculeazaDiscountHrana();

};

//constructor fara parametrii
Hrana::Hrana()
{
	this->nume = "Anonim";
	this->pret = 0;
	this->tipAnimal = "Anonim";
	this->estePtProblemeSpeciale = false;
}

//constructor cu toti parametrii
Hrana::Hrana(string nume, double pret, string tipAnimal, bool estePtProblemeSpeciale)
{
	this->nume = nume;
	this->pret = pret;
	this->tipAnimal = tipAnimal;
	this->estePtProblemeSpeciale = estePtProblemeSpeciale;
}

//copy constructor
Hrana::Hrana(const Hrana& other)
{
	this->nume = other.nume;
	this->pret = other.pret;
	this->tipAnimal = other.tipAnimal;
	this->estePtProblemeSpeciale = other.estePtProblemeSpeciale;
}

//overload operator=
Hrana& Hrana::operator=(const Hrana& other)
{
	if (this != &other)
	{
		this->nume = other.nume;
		this->pret = other.pret;
		this->tipAnimal = other.tipAnimal;
		this->estePtProblemeSpeciale = other.estePtProblemeSpeciale;
	}
	return *this;
}

ostream& Hrana::afisare(ostream& out) const
{
	out << "\nNume: " << this->nume;
	out << "\nPret: " << this->pret;
	out << "\nTip animal: " << this->tipAnimal;
	out << "\nEste pentru probleme speciale: " << this->estePtProblemeSpeciale;
	return out;
}

istream& Hrana::citire(istream& in)
{
	cout << "\nNume: " ;
	in >> this->nume;

	cout << "\nPret: " ;
	try
	{
		in >> this->pret;
		if (this->pret <= 0)
		{
			throw exceptiePretHrana;
		}
	}
	catch (ExceptiePretHrana& e)
	{
		while (this->pret <= 0)
		{
			cout << e.what() << endl;
			in >> this->pret;
		}
	}
	

	cout << "\nTip animal: ";
	try
	{
		in >> this->tipAnimal;
		if (this->tipAnimal != "caine" && this->tipAnimal != "pisica" && this->tipAnimal != "Caine" && this->tipAnimal != "Pisica")
		{
			throw exceptieTipAnimal;
		}
	}
	catch (ExceptieTipAnimal& e)
	{
		while (this->tipAnimal != "caine" && this->tipAnimal != "pisica" && this->tipAnimal != "Caine" && this->tipAnimal != "Pisica")
		{
			cout << e.what() << endl;
			in >> this->tipAnimal;
		}
	}
	

	cout << "\nEste pentru probleme speciale: ";
	in >> this->estePtProblemeSpeciale;

	return in;
}

//overload operator<<
ostream& operator<<(ostream& out, const Hrana& h)
{
	return h.afisare(out);
}

// overload operator>>
istream& operator>>(istream& in, Hrana& h)
{
	return h.citire(in);
}

// destructor
Hrana::~Hrana()
{
	//cout << "\nDistruge hrana:";
	//cout << this->nume << endl;
}

//function
double Hrana::calculeazaDiscountHrana()
{
	double discount = 0;
	if (this->estePtProblemeSpeciale == true)
		discount = 10 * 0.01 * this->pret;
	return discount;
}

class ExceptieGrame :public exception
{
public:
	virtual const char* what() const throw() {

		return "Cantitatea de hrana uscata ar trebuie sa fie mai mare decat 0. Va rugam introduceti din nou :";
	}
}exceptieGrame;

class HranaUscata : public Hrana
{
private:
	int grame;

public:
	//setter
	void setGrame(int grame) { this->grame = grame; }

	//getter
	int getGrame() { return this->grame; }

	//constructor fara parametrii
	HranaUscata();

	//constructor cu toti parametrii
	HranaUscata(string nume, double pret, string tipAnimal, bool estePtProblemeSpeciale, int grame);

	//copy constructor
	HranaUscata(const HranaUscata& other);

	//overload operator=
	HranaUscata& operator=(const HranaUscata& other);

	//afisare 
	ostream& afisare(ostream& out) const;

	//citire
	istream& citire(istream& in);

	//destructor
	~HranaUscata();

	//function
	double calculeazaDiscountHranaUscata();
};

//constructor fara parametrii
HranaUscata::HranaUscata() :Hrana()
{
	this->grame = 0;
}

//constructor cu toti parametrii
HranaUscata::HranaUscata(string nume, double pret, string tipAnimal, bool estePtProblemeSpeciale, int grame)
	:Hrana(nume, pret, tipAnimal, estePtProblemeSpeciale)
{
	this->grame = grame;
}

//copy constructor
HranaUscata::HranaUscata(const HranaUscata& other) :Hrana(other)
{
	this->grame = other.grame;
}

//overload operator=
HranaUscata& HranaUscata::operator=(const HranaUscata& other)
{
	if (this != &other)
	{
		Hrana::operator=(other);
		this->grame = other.grame;

	}
	return *this;
}

//afisare
ostream& HranaUscata::afisare(ostream& out) const
{
	Hrana::afisare(out);
	out << "\nGrame: " << this->grame << endl;
	return out;

}

//citire
istream& HranaUscata::citire(istream& in)
{
	Hrana::citire(in);
	cout << "\nGrame: ";
	try 
	{
		in >> this->grame;
		if (this->grame <= 0)
		{
			throw exceptieGrame;
		}
	}
	catch (ExceptieGrame& e)
	{
		while (this->grame <= 0)
		{
			cout << e.what() << endl;
			in >> this->grame;
		}
	}
	
	cout << endl;
	return in;
}

//destructor
HranaUscata::~HranaUscata()
{
	//cout << "\nDistruge hrana uscata " << endl;
}

//function: 
double HranaUscata::calculeazaDiscountHranaUscata()
{
	double discountTotal = 0; // se calculeaza la totalul de grame, NU pe suta de grame

	if (this->grame >= 500 && this->grame < 1500)
		discountTotal = 15 * 0.01 * this->pret;
	else
		if (this->grame >= 1500)
			discountTotal = 25 * 0.01 * this->pret;

	if (((Hrana)*this).calculeazaDiscountHrana() == 0)
		return discountTotal;
	else
		return discountTotal + ((Hrana)*this).calculeazaDiscountHrana();

}

class ExceptieNrPlicuri :public exception
{
public:
	virtual const char* what() const throw() {

		return "Cantitatea de hrana umeda ar trebuie sa fie mai mare decat 0. Va rugam introduceti din nou :";
	}
}exceptieNrPlicuri;

class HranaUmeda : virtual public Hrana
{
protected:
	int nrPlicuri;

public:
	//setter
	void setNrPlicuri(int nrPlicuri) { this->nrPlicuri = nrPlicuri; }

	//getter
	int getNrPlicuri() { return this->nrPlicuri; }

	//constructor fara parametrii
	HranaUmeda();

	//constructor cu toti parametrii
	HranaUmeda(string nume, double pret, string tipAnimal, bool estePtProblemeSpeciale, int nrPlicuri);

	//copy constructor
	HranaUmeda(const HranaUmeda& other);

	//overload operator=
	HranaUmeda& operator=(const HranaUmeda& other);

	//afisare
	ostream& afisare(ostream& out) const;

	//overload operator>>
	istream& citire(istream& in);

	//destructor
	~HranaUmeda();

	//function
	double calculeazaDiscountHranaUmeda();
};

//constructor fara parametrii
HranaUmeda::HranaUmeda() :Hrana()
{
	//cout<<"\nConstructor fara parametrii pentru hrana umeda";
	this->nrPlicuri = 0;
}

//constructor cu toti parametrii
HranaUmeda::HranaUmeda(string nume, double pret, string tipAnimal, bool estePtProblemeSpeciale, int nrPlicuri) 
			:Hrana(nume, pret, tipAnimal, estePtProblemeSpeciale)
{
	//cout << "Constructor cu toti parametrii pentru hrana umeda:\n";
	this->nrPlicuri = nrPlicuri;
}

//copy constructor
HranaUmeda::HranaUmeda(const HranaUmeda& other) :Hrana(other)
{
	this->nrPlicuri = other.nrPlicuri;
}

//overload operator=
HranaUmeda& HranaUmeda :: operator=(const HranaUmeda& other)
{
	if (this != &other)
	{
		Hrana::operator=(other);
		this->nrPlicuri = other.nrPlicuri;
	}
	return *this;
}

//afisare
ostream& HranaUmeda::afisare(ostream& out) const
{
	Hrana::afisare(out);
	out << "\nNumar plicuri: " << this->nrPlicuri << endl;
	return out;
}

//citire
istream& HranaUmeda::citire(istream& in)
{
	Hrana::citire(in);
	cout << "\nNumar plicuri: ";
	try
	{
		in >> this->nrPlicuri;
		if (this->nrPlicuri <= 0)
		{
			throw exceptieNrPlicuri;
		}
	}
	catch (ExceptieNrPlicuri& e)
	{
		while (this->nrPlicuri <= 0)
		{
			cout << e.what() << endl;
			in >> this->nrPlicuri;
		}
	}
	
	cout << endl;
	return in;
}

//destructor
HranaUmeda::~HranaUmeda()
{
	//cout << "\nDistruge hrana umeda " << endl;
}

//function
double HranaUmeda::calculeazaDiscountHranaUmeda()
{
	double discountPerPlic = 0;
	double discountTotal = 0;

	if (this->nrPlicuri >= 15 && this->nrPlicuri < 35)
		discountPerPlic = 10 * 0.01 * this->pret;
	else
		if (this->nrPlicuri >= 35)
			discountPerPlic = 20 * 0.01 * this->pret;

	discountTotal = discountPerPlic * this->nrPlicuri;

	if (((Hrana)*this).calculeazaDiscountHrana() == 0)
		return discountTotal;
	else
		return discountTotal + ((Hrana)*this).calculeazaDiscountHrana();
}

class ExceptieSexAnimal :public exception
{
public:
	virtual const char* what() const throw() {

		return "Sexul ar trebui sa fie M sau F. Va rugam introduceti din nou :";
	}
}exceptieSexAnimal;

class ExceptieVarstaAnimal :public exception
{
public:
	virtual const char* what() const throw() {

		return "Varsta ar trebui sa fie mai mare sau egala cu 0. Va rugam introduceti din nou :";
	}
}exceptieVarstaAnimal;

class ExceptieGreutateAnimal :public exception
{
public:
	virtual const char* what() const throw() {

		return "Greutatea ar trebui sa fie mai mare decat 0. Va rugam introduceti din nou :";
	}
}exceptieGreutateAnimal;

class ExceptiePretAnimal :public exception
{
public:
	virtual const char* what() const throw() {

		return "Pretul ar trebui sa fie mai mare decat 0. Va rugam introduceti din nou :";
	}
}exceptiePretAnimal;


class Animal
{
protected:
	string nume;
	char sex;
	int varsta;
	double greutate;
	double pret;
	bool areProblemeSpeciale;

public:
	//setters
	void setNume(string nume) { this->nume = nume; }
	void setSex(char sex) { this->sex = sex; }
	void setVarsta(int varsta) { this->varsta = varsta; }
	void setGreutate(double greutate) { this->greutate = greutate; }
	void setPret(double pret) { this->pret = pret; }
	void setAreProblemeSpeciale(bool areProblemeSpeciale) { this->areProblemeSpeciale = areProblemeSpeciale; }

	//getters
	string getNume() { return this->nume; }
	char getSex() { return this->sex; }
	int getVarsta() { return this->varsta; }
	double getGreutate() { return this->greutate; }
	double getPret() { return this->pret; }
	bool getAreProblemeSpeciale() { return this->areProblemeSpeciale; }

	//constructor fara parametrii
	Animal();

	//costructor cu toti parametrii
	Animal(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale);

	//copy constructor
	Animal(const Animal& other);

	//overload operator=
	Animal& operator=(const Animal& other);

	//afisare
	virtual ostream& afisare(ostream& out) const;
	 
	//citire
	virtual istream& citire(istream& in);

	//overload operator<<
	friend ostream& operator<<(ostream& out, const Animal& a);

	//overload operator>>
	friend istream& operator>>(istream& in, Animal& a);

	//destructor
	~Animal();

	//function
	virtual bool verificaObezitate() = 0;
};

//constructor fara parametrii
Animal::Animal()
{
	//cout << "Constructor fara parametrii pentru animal:\n";
	this->nume = "Anonim";
	this->sex = '-';
	this->varsta = 0;
	this->greutate = 0;
	this->pret = 0;
	this->areProblemeSpeciale = false;
}

//constructor cu toti parametrii
Animal::Animal(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale)
{
	//cout << "Constructor cu toti parametrii pentru animal:\n";
	this->nume = nume;
	this->sex = sex;
	this->varsta = varsta;
	this->greutate = greutate;
	this->pret = pret;
	this->areProblemeSpeciale = areProblemeSpeciale;
}

//copy constructor
Animal::Animal(const Animal& other)
{
	this->nume = other.nume;
	this->sex = other.sex;
	this->varsta = other.varsta;
	this->greutate = other.greutate;
	this->pret = other.pret;
	this->areProblemeSpeciale = other.areProblemeSpeciale;
}

//overload operator=
Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
	{
		this->nume = other.nume;
		this->sex = other.sex;
		this->varsta = other.varsta;
		this->greutate = other.greutate;
		this->pret = other.pret;
		this->areProblemeSpeciale = other.areProblemeSpeciale;
	}
	return *this;
}

//afisare
ostream& Animal::afisare(ostream& out) const
{
	out << "\nNume: " << this->nume;
	out << "\nSex: " << this->sex;
	out << "\nVarsta: " << this->varsta;
	out << "\nGreutate: " << this->greutate;
	out << "\nPret: " << this->pret;
	out << "\nAre probleme speciale: " << this->areProblemeSpeciale;
	return out;
}

//citire
istream& Animal::citire(istream& in)
{
	cout << "\nNume: ";
	in >> this->nume;

	cout << "\nSex: ";
	try
	{
		in >> this->sex;
		if (this->sex != 'M' && this->sex != 'F')
		{
			throw exceptieSexAnimal;
		}
	}
	catch (ExceptieSexAnimal& e)
	{
		while (this->sex != 'M' && this->sex != 'F')
		{
			cout << e.what() << endl;
			in >> this->sex;
		}
	}
	
	cout << "\nVarsta: ";
	try
	{
		in >> this->varsta;
		if (this->varsta < 0)
		{
			throw exceptieVarstaAnimal;
		}
	}
	catch (ExceptieVarstaAnimal& e)
	{
		while (this->varsta < 0)
		{
			cout << e.what() << endl;
			in >> this->varsta;
		}
	}
	

	cout << "\nGreutate: ";
	try
	{
		in >> this->greutate;
		if (this->greutate <= 0)
		{
			throw exceptieGreutateAnimal;
		}
	}
	catch (ExceptieGreutateAnimal& e)
	{
		if (this->greutate <= 0)
		{
			cout << e.what() << endl;
			in >> this->greutate;
		}
	}
	

	cout << "\nPret: ";
	try
	{
		in >> this->pret;
		if (this->pret <= 0)
		{
			throw exceptiePretAnimal;
		}
	}
	catch(ExceptiePretAnimal& e)
	{
		if (this->pret <= 0)
		{
			cout << e.what() << endl;
			in >> this->pret;
		}
	}
	

	cout << "\nAre probleme speciale: ";
	in >> this->areProblemeSpeciale;

	return in;
}

//overload operator<<
ostream& operator<<(ostream& out, const Animal& a)
{
	return a.afisare(out);
}

//overload operator>>
istream& operator>>(istream& in, Animal& a)
{
	return a.citire(in);
}

//destructor
Animal::~Animal()
{
	//cout << "\nDistruge animalul: ";
	//cout << this->nume << endl;
}

class Pisica : public Animal
{
protected:
	bool areGheareTaiate;

public:
	//setter
	void setAreGheareTaiate(bool areGheareTaiate) { this->areGheareTaiate = areGheareTaiate; }

	//getter
	bool getAreGheareTaiate() { return this->areGheareTaiate; }

	//constructor fara parametrii
	Pisica();

	//constructor cu toti parametrii
	Pisica(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool areGheareTaiate);

	//copy constructor
	Pisica(const Pisica& other);

	//overload operator=
	Pisica& operator=(const Pisica& other);

	//oafisare
	ostream& afisare(ostream& out) const;

	//citire
	istream& citire(istream& in);

	//destructor
	~Pisica();

	//function
	bool verificaObezitate();

};

//constructor fara parametrii
Pisica::Pisica() :Animal()
{
	//cout << "Constructor fara parametrii pentru pisica:\n";
	this->areGheareTaiate = false;

}

//constructor cu toti parametrii
Pisica::Pisica(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool areGheareTaiate)
	:Animal(nume, sex, varsta, greutate, pret, areProblemeSpeciale)
{
	this->areGheareTaiate = areGheareTaiate;
}

//copy constructor
Pisica::Pisica(const Pisica& other) : Animal(other)
{
	this->areGheareTaiate = other.areGheareTaiate;
}

//overload operator=
Pisica& Pisica :: operator=(const Pisica& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		this->areGheareTaiate = other.areGheareTaiate;
	}
	return *this;
}

//afisare
ostream& Pisica::afisare(ostream& out) const
{
	Animal::afisare(out);
	out << "\nAre gheare taiate: " << this->areGheareTaiate;
	return out;
}

//citire
istream& Pisica::citire(istream& in)
{
	Animal::citire(in);
	cout << "\nAre gheare taiate: ";
	in >> this->areGheareTaiate;
	cout << endl;
	return in;
}

//destructor
Pisica::~Pisica()
{
	//cout << "\nDistruge pisica:" << endl;
}

//function 
bool Pisica::verificaObezitate()
{
	bool obezitatePisica = false;
	int criteriuObezitatePisica;
	if (this->varsta < 2)
		criteriuObezitatePisica = 7;
	else
	{
		if (this->varsta >= 2 && this->varsta <= 10)
			criteriuObezitatePisica = 12;
		else
			criteriuObezitatePisica = 10;
	}

	if (this->greutate >= criteriuObezitatePisica)
	{
		this->areProblemeSpeciale = true;
		obezitatePisica = true;
	}

	return obezitatePisica;
}

class PuiPisica : public Pisica
{
private:
	bool areOchiiDeschisi;

public:
	//setter
	void setAreOchiiDeschisi(bool areOchiiDeschisi) { this->areOchiiDeschisi = areOchiiDeschisi; }

	//getter
	bool getAreOchiiDeschisi() { return this->areOchiiDeschisi; }

	//constructor fara parametrii
	PuiPisica();

	//constructor cu toti parametrii
	PuiPisica(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool areGheareTaiate, bool areOchiiDeschisi);

	//copy constructor
	PuiPisica(const PuiPisica& other);

	//overload operator=
	PuiPisica& operator=(const PuiPisica& other);

	//afisare
	ostream& afisare(ostream& out) const;

	//citire
	istream& citire(istream& in);

	//destructor
	~PuiPisica();

	//function
	bool poateFiAdoptat();
};

//constructor fara parametrii
PuiPisica::PuiPisica() :Pisica()
{
	this->areOchiiDeschisi = false;
}

//constructor cu toti parametrii
PuiPisica::PuiPisica(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool areGheareTaiate, bool areOchiiDeschisi)
		:Pisica(nume, sex, varsta, greutate, pret, areProblemeSpeciale, areGheareTaiate)
{
	this->areOchiiDeschisi = areOchiiDeschisi;
}

//copy constructor
PuiPisica::PuiPisica(const PuiPisica& other) :Pisica(other)
{
	this->areOchiiDeschisi = other.areOchiiDeschisi;
}

//overload operator=
PuiPisica& PuiPisica::operator=(const PuiPisica& other)
{
	if (this != &other)
	{
		Pisica::operator=(other);
		this->areOchiiDeschisi = other.areOchiiDeschisi;
	}
	return *this;
}

//afisare
ostream& PuiPisica::afisare(ostream& out) const
{
	Pisica::afisare(out);
	out << "\nAre ochii deschisi: " << this->areOchiiDeschisi << endl;
	return out;
}

//citire
istream& PuiPisica::citire(istream& in)
{
	Pisica::citire(in);
	cout << "\nAre ochii deschisi: ";
	in >> this->areOchiiDeschisi;
	cout << endl;
	return in;
}

//destructor
PuiPisica::~PuiPisica()
{
	//cout << "\nDistruge PuiPisica" << endl;
}

//function
bool PuiPisica::poateFiAdoptat()
{
	bool poateFiAdoptat = false;
	if (this->areOchiiDeschisi == true)
		poateFiAdoptat = true;

	return poateFiAdoptat;
	
}

class Caine :public Animal
{
private:
	bool esteDresat;

public:
	//setter
	void setEsteDresat(bool esteDresat) { this->esteDresat = esteDresat; }

	//getter
	bool getEsteDresat() { return this->esteDresat; }

	//constructor fara parametrii
	Caine();

	//constructor cu toti parametrii
	Caine(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool esteDresat);

	//copy constructor
	Caine(const Caine& other);

	//overload operator=
	Caine& operator=(const Caine& other);

	//afisare
	ostream& afisare(ostream& out) const;

	//overload operator>>
	istream& citire(istream& in);

	//destructor
	~Caine();

	//function
	bool verificaObezitate();
};

//constructor fara parametrii
Caine::Caine() :Animal()
{
	this->esteDresat = false;
}

//constructor cu toti parametrii
Caine::Caine(string nume, char sex, int varsta, double greutate, double pret, bool areProblemeSpeciale, bool esteDresat)
	:Animal(nume, sex, varsta, greutate, pret, areProblemeSpeciale)
{
	this->esteDresat = esteDresat;
}

//copy constructor
Caine::Caine(const Caine& other) :Animal(other)
{
	this->esteDresat = other.esteDresat;
}

//overload operator=
Caine& Caine::operator=(const Caine& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		this->esteDresat = other.esteDresat;
	}
	return *this;
}

//afisare
ostream& Caine::afisare(ostream& out) const
{
	Animal::afisare(out);
	out << "\nEste dresat: " << this->esteDresat << endl;
	return out;
}

//citire
istream& Caine::citire(istream& in)
{
	Animal::citire(in);
	cout << "\nEste dresat: ";
	in >> this->esteDresat;
	cout << endl;
	return in;
}

//destructor
Caine::~Caine()
{
	//cout << "\nDistruge caine " << endl;
}

//function
bool Caine::verificaObezitate()
{
	bool obezitateCaine = false;
	int criteriuObezitateCaine;
	if (this->varsta < 2)
		criteriuObezitateCaine = 25;
	else
	{
		if (this->varsta >= 2 && this->varsta <= 10)
			criteriuObezitateCaine = 35;
		else
			criteriuObezitateCaine = 30;
	}

	if (this->greutate >= criteriuObezitateCaine)
	{
		this->areProblemeSpeciale = true;
		obezitateCaine = true;
	}

	return obezitateCaine;
}

class ExceptieRating :public exception
{
public:
	virtual const char* what() const throw() {

		return "Ratingul ar trebui sa fie intre 0 si 5. Va rugam introduceti din nou :";
	}
}exceptieRating;

class ExceptieSexClient : public exception
{
public:
	virtual const char* what() const throw() {

		return "Sexul ar trebui sa fie M sau F. Va rugam introduceti din nou :";
	}
}exceptieSex;

class Client
{
protected:
	string numePrenume;
	char sex;
	double rating;
	int animaleDetinute;

public:
	//setters
	void setNumePrenume(string numePrenume) { this->numePrenume = numePrenume; }
	void setSex(char sex) { this->sex = sex; }
	void setRating(double rating) { this->rating = rating; }
	void setAnimaleDetinute(int animaleDetinute) { this->animaleDetinute = animaleDetinute; }

	//getters
	string getNumePrenume() { return this->numePrenume; }
	char getSex() { return this->sex; }
	double getRating() { return this->rating; }
	int getAnimaleDetinute() { return this->animaleDetinute; }

	//costructor fara parametrii
	Client();

	//constructor cu toti parametrii
	Client(string numePrenume, char sex, double rating, int animaleDetinute);

	//copy constructor
	Client(const Client& other);

	//overload operator=
	Client& operator=(const Client& other);

	//afisare
	virtual ostream& afisare(ostream& out) const;

	//citire
	virtual istream& citire(istream& in);

	//overload operator<<
	friend ostream& operator<<(ostream& out, const Client& c);

	//overload operator>>
	friend istream& operator>>(istream& in, Client& c);

	//destructor
	~Client();

	//function 
	bool poateAdopta(Animal& a) const;
};

//constructor fara parametrii
Client::Client()
{
	this->numePrenume = "Anonim";
	this->sex = '-';
	this->rating = 0;
	this->animaleDetinute = 0;
}

//constructor cu toti parametrii
Client::Client(string numePrenume, char sex, double rating, int animaleDetinute)
{
	this->numePrenume = numePrenume;
	this->sex = sex;
	this->rating = rating;
	this->animaleDetinute = animaleDetinute;
}

//copy constructor
Client::Client(const Client& other)
{
	this->numePrenume = other.numePrenume;
	this->sex = other.sex;
	this->rating = other.rating;
	this->animaleDetinute = other.animaleDetinute;
}

//overload operator=
Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		this->numePrenume = other.numePrenume;
		this->sex = other.sex;
		this->rating = other.rating;
		this->animaleDetinute = other.animaleDetinute;
	}
	return *this;
}

//afisare
ostream& Client::afisare(ostream& out) const
{
	out << "\nNume prenume: " << this->numePrenume;
	out << "\nSex: " << this->sex;
	out << "\nRating: " << this->rating;
	out << "\nAnimale detinute: " << this->animaleDetinute;
	return out;
}

//citire
istream& Client::citire(istream& in)
{
	cout << "\nNume prenume: ";
	in >> this->numePrenume;

	cout << "\nSex: ";
	try
	{
		in >> this->sex;
		if (this->sex != 'M' && this->sex != 'F')
		{
			throw exceptieSex;
		}
	}
	catch (ExceptieSexClient& e)
	{
		while (this->sex != 'M' && this->sex != 'F')
		{
			cout << e.what() << endl;
			in >> this->sex;
		}
	}
	
	cout << "\nRating: ";
	try
	{
		in >> this->rating;
		if (this->rating < 0 || this->rating > 5)
		{
			throw exceptieRating;
		}
	}
	catch (ExceptieRating& e)
	{
		while (this->rating < 0 || this->rating > 5)
		{
			cout << e.what() << endl;
			in >> this->rating;
		}

	}
	
	cout << "\nAnimale detinute: ";
	in >> this->animaleDetinute;
	return in;
	
	
}
//overload operator<<
ostream& operator<<(ostream& out, const Client& c)
{
	return c.afisare(out);
}

//overload operator>>
istream& operator>>(istream& in, Client& c)
{
	return c.citire(in);
}

//destructor
Client::~Client()
{
	//cout << "\nDistruge client ";
	//cout << this->numePrenume << endl;
}

//function 
bool Client::poateAdopta(Animal& a) const
{
	bool poateAdopta = true;

	if (this->rating <= 2.5 && this->animaleDetinute >= 5)
		poateAdopta = false;
	else
		if (this->animaleDetinute >= 3 && a.getAreProblemeSpeciale() == true)
			poateAdopta = false;

	return poateAdopta;
}

class Adult :public Client
{
private:
	int membriiCasa;
	bool calatoresteMult;

public:
	//setters
	void setMembriiCasa(int membriiCasa) { this->membriiCasa = membriiCasa; }
	void setCalatoresteMult(bool calatoresteMult) { this->calatoresteMult = calatoresteMult; }

	//getters
	int getMembriiCasa() { return this->membriiCasa; }
	bool getCalaltoresteMult() { return this->calatoresteMult; }

	//constructor fara parametrii
	Adult();

	//constructor cu toti parametrii
	Adult(string numePrenume, char sex, double rating, int animaleDetinute, int membriiCasa, bool calatoresteMult);

	//copy constructor
	Adult(const Adult& other);

	//overload operator=
	Adult& operator=(const Adult& other);

	//afisare
	ostream& afisare(ostream& out) const;

	//citire
	istream& citire(istream& in);

	//destructor 
	~Adult();

	//function
	bool poateAdoptaAdultul(Animal& a);
};

//constructor fara parametrii
Adult::Adult() :Client()
{
	this->membriiCasa = 0;
	this->calatoresteMult = false;
}

//constructor cu toti parametrii
Adult::Adult(string numePrenume, char sex, double rating, int animaleDetinute, int membriiCasa, bool calatoresteMult)
	:Client(numePrenume, sex, rating, animaleDetinute)
{
	this->membriiCasa = membriiCasa;
	this->calatoresteMult = calatoresteMult;
}

//copy constructor
Adult::Adult(const Adult& other) :Client(other)
{
	this->membriiCasa = other.membriiCasa;
	this->calatoresteMult = other.calatoresteMult;
}

//overload operator=
Adult& Adult::operator=(const Adult& other)
{
	if (this != &other)
	{
		Client::operator=(other);
		this->membriiCasa = other.membriiCasa;
		this->calatoresteMult = other.calatoresteMult;
	}
	return *this;
}

//afisare
ostream& Adult::afisare(ostream& out) const
{
	Client::afisare(out);
	out << "\nMembrii casa: " << this->membriiCasa;
	out << "\nCalatoreste mult: " << this->calatoresteMult;
	out << endl;
	return out;
}

//citire
istream& Adult::citire(istream& in)
{
	Client::citire(in);
	cout << "\nMembrii casa: ";
	in >> this->membriiCasa;
	cout << "\nCalatoreste mult: ";
	in >> this->calatoresteMult;
	cout << endl;
	return in;
}

//destructor
Adult::~Adult()
{
	//cout << "\nDistruge adult " << endl;
}

//function
bool Adult::poateAdoptaAdultul(Animal& a)
{
	bool poateAdopta = true;

	if (this->calatoresteMult == true && this->membriiCasa == 1)
		poateAdopta = false;

	if (poateAdopta == true && this->poateAdopta(a) == true)
		return true;
	else
		return false;
}

class Pensionar : public Client
{
private:
	bool areProblemeSanatate;

public:
	//setter
	void setAreProblemeSanatate(bool areProblemeSanatate) { this->areProblemeSanatate = areProblemeSanatate; }

	//getter
	bool getAreProblemeSanatate() { return this->areProblemeSanatate; }

	//constructor fara parametrii
	Pensionar();

	//constructor cu toti parametrii
	Pensionar(string numePrenume, char sex, double rating, int animaleDetinute, bool areProblemeSanatate);

	//copy constructor
	Pensionar(const Pensionar& other);

	//overload operator=
	Pensionar& operator=(const Pensionar& other);

	//overload operator<<
	ostream& afisare(ostream& out) const;

	//overload operator>>
	istream& citire(istream& in);

	//destructor
	~Pensionar();

	//function
	bool poateAdoptaPensionarul(Animal& a);

};

//constructor fara parametrii
Pensionar::Pensionar() :Client()
{
	this->areProblemeSanatate = false;
}

//constructor cu toti parametrii
Pensionar::Pensionar(string numePrenume, char sex, double rating, int animaleDetinute, bool areProblemeSanatate)
	: Client(numePrenume, sex, rating, animaleDetinute)
{
	this->areProblemeSanatate = areProblemeSanatate;
}

//copy constructor
Pensionar::Pensionar(const Pensionar& other) :Client(other)
{
	this->areProblemeSanatate = other.areProblemeSanatate;
}

//overload operator=
Pensionar& Pensionar::operator=(const Pensionar& other)
{
	if (this != &other)
	{
		Client::operator=(other);
		this->areProblemeSanatate = other.areProblemeSanatate;
	}
	return *this;
}

//overload operator<<
ostream& Pensionar::afisare(ostream& out) const
{
	Client::afisare(out);
	out << "\nAre probleme de sanatate: " << this->areProblemeSanatate;
	out << endl;
	return out;
}

//overload operator>>
istream& Pensionar::citire(istream& in)
{
	Client::citire(in);
	cout << "\nAre probleme de sanatate: ";
	in >> this->areProblemeSanatate;
	cout << endl;
	return in;
}

//destructor
Pensionar::~Pensionar()
{
	//cout << "\nDistruge pensionarul: ";
	//cout << endl;
}

//function
bool Pensionar::poateAdoptaPensionarul(Animal& a)
{
	bool poateAdopta = true;

	if (this->areProblemeSanatate == true && a.getAreProblemeSpeciale() == true)
		poateAdopta = false;

	if (poateAdopta == true && this->poateAdopta(a) == true)
		return true;
	else
		return false;
}

class Meniu
{
private:
	static Meniu* obiect;

	Meniu() {}


public:
	static Meniu* getInstance() 
	{
		if (!obiect)
			obiect = new Meniu();

		return obiect;
	}

	void meniu()
	{
		vector<Animal*>vectorAnimale;
		list<Client*>listaClienti;
		map<Hrana*, int>mapHrana;

		list<Client>::iterator  it;
		map<Hrana*, int>::iterator itr;

		int indexAnimale = 0;
		int indexClienti = 0;

		int input = -1;

		while (input != 0)
		{
			cout << "\nALEGETI OPTIUNEA: " << endl;
			cout << " 0. Exit\n";
			cout << " 1. Creeaza pisica\n";
			cout << " 2. Creeaza pui pisica\n";
			cout << " 3. Creeaza caine\n";

			cout << " 4. Creeaza adult\n";
			cout << " 5. Creeaza pensionar\n";
			
			cout << " 6. Creeaza hrana uscata\n";
			cout << " 7. Creeaza hrana umeda\n";

			cout << " 8. Afiseaza toate pisicile\n";
			cout << " 9. Afiseaza toti puii de pisica\n";
			cout << "10. Afiseaza toti cainii\n";
			cout << "11. Afiseaza toate animalele\n";
			
			cout << "12. Afiseaza toti adultii\n";
			cout << "13. Afiseaza toti pensionarii\n";
			cout << "14. Afiseaza toti clientii\n";

			cout << "15. Afiseaza toata hrana uscata\n";
			cout << "16. Afiseaza toata hrana umeda\n";
			cout << "17. Afiseaza toata hrana\n";


			cin >> input;
			switch (input)
			{
			case 0:
				cout << "Iesire din program! " << endl;
				break;

			case 1:
			{
				Animal* p = new Pisica();
				cin >> *p;
				vectorAnimale.push_back(p);
				break;
			}

			case 2:
			{
				Animal* pp = new PuiPisica();
				cin >> *pp;
				vectorAnimale.push_back(pp);
				break;
			}

			case 3:
			{
				Animal* c = new Caine();
				cin >> *c;
				vectorAnimale.push_back(c);
				break;
			}

			case 4:
			{
				Client* cl = new Adult();
				cin >> *cl;
				listaClienti.push_back(cl);
				break;
			}

			case 5:
			{
				Client* pen = new Pensionar();
				cin >> *pen;
				listaClienti.push_back(pen);
				break;
			}

			case 6:
			{
				HranaUscata* hu = new HranaUscata();
				cin >> *hu;
				mapHrana.insert({ hu, hu->getGrame()});
				break;
			}

			case 7:
			{
				HranaUmeda* hum = new HranaUmeda();
				cin >> *hum;
				mapHrana.insert({ hum, hum->getNrPlicuri() });

				break;
			}

			case 8:
			{
				bool estePisicaAdaugata = false;
				for (int i = 0; i < vectorAnimale.size(); i++)
				{
					if ((typeid(*vectorAnimale[i])) == (typeid(Pisica)))
					{
						cout << dynamic_cast<Pisica&>(*vectorAnimale[i]) << endl;
						estePisicaAdaugata = true;
					}

				}

				if (estePisicaAdaugata == false)
				{
					cout << "Nu avem pisici adaugate!\n";
				}

				break;
			}

			case 9:
			{
				bool estePuiPisicaAdaugat = false;
				for (int i = 0; i < vectorAnimale.size(); i++)
				{
					if ((typeid(*vectorAnimale[i])) == (typeid(PuiPisica)))
					{
						cout << dynamic_cast<PuiPisica&>(*vectorAnimale[i]) << endl;
						estePuiPisicaAdaugat = true;
					}
				}

				if (estePuiPisicaAdaugat == false)
				{
					cout << "Nu avem pui de pisici adaugati!\n";
				}
				break;
			}

			case 10:
			{
				bool esteCaineAdaugat = false;
				for (int i = 0; i < vectorAnimale.size(); i++)
				{
					if ((typeid(*vectorAnimale[i])) == (typeid(Caine)))
					{
						cout << dynamic_cast<Caine&>(*vectorAnimale[i]) << endl;
						esteCaineAdaugat = true;
					}

				}

				if (esteCaineAdaugat == false)
				{
					cout << "Nu avem caini adaugati!\n";
				}
				break;
			}

			case 11:
			{
				if (vectorAnimale.size())
				{
					for (int i = 0; i < vectorAnimale.size(); i++)
					{
						cout << *vectorAnimale[i] << '\n';
					}
				}
				else
					cout << "Nu exista niciun animal adaugat!\n";
					
				break;
			}

			case 12:
			{
				bool esteAdultAdaugat = false;


				for (auto it = listaClienti.begin(); it != listaClienti.end(); ++it)
				{
					if ( typeid(**it).name() == typeid(Adult).name() )
					{
						cout << static_cast<Adult&>(**it) << endl;
						esteAdultAdaugat = true;
					}
					
				
				}

				if (esteAdultAdaugat == false)
				{
					cout << "Nu avem adulti adaugati!\n";
				}

				
				break;
			}

			case 13:
			{
				bool estePensionarAdaugat = false;


				for (auto it = listaClienti.begin(); it != listaClienti.end(); ++it)
				{
					if (typeid(**it).name() == typeid(Pensionar).name())
					{
						cout << static_cast<Pensionar&>(**it) << endl;
						estePensionarAdaugat = true;
					}


				}

				if (estePensionarAdaugat == false)
				{
					cout << "Nu avem adulti adaugati!\n";
				}
				break;
			}

			case 14:
			{
				if (listaClienti.size())
				{
					for (auto it = listaClienti.begin(); it != listaClienti.end(); ++it)
					
						cout << **it << '\n';
				}
				break;
			}

			case 15:
			{
				cout << "\tNumeHranaUscata\tGramaj\n";
				for (itr = mapHrana.begin(); itr != mapHrana.end(); ++itr)
					if(typeid(*itr->first) ==typeid(HranaUscata))
					{
						cout << '\t' << (itr->first)->getNume()
							<< '\t' << '\t' << itr->second << '\n';
					}
				break;
			}

			case 16:
			{
				cout << "\tNumeHranaUmeda\tGramaj\n";
				for (itr = mapHrana.begin(); itr != mapHrana.end(); ++itr)
					if (typeid(*itr->first) == typeid(HranaUmeda))
					{
						cout << '\t' << (itr->first)->getNume()
							<< '\t' << '\t' << itr->second << '\n';
					}
				break;
			}

			case 17:
			{
				cout << "\tNumeHrana\tGramaj\n";
				for (itr = mapHrana.begin(); itr != mapHrana.end(); ++itr)
					if (typeid(*itr->first) == typeid(HranaUscata))
					{
						cout << '\t' << (itr->first)->getNume()
							<< '\t' << '\t' << itr->second << " " << "grame" << '\n';
					}
					else
					{
						cout << '\t' << (itr->first)->getNume()
							<< '\t' << '\t' << itr->second << " " << "plicuri" << '\n';
					}
				break;
			}

			default:
				cout << "Optiunea nu exista! " << endl;
				break;
			}
		}
	}

};

Meniu* Meniu::obiect = 0;


int main()
{
	Meniu* meniulMeu = meniulMeu->getInstance();
	meniulMeu->meniu();

	return 0;
}