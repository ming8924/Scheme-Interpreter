/**
 * \mainpage COMP151H Programming Assignment 5, Spring 2009
 *
 * \author **CHEN Ming**
 * \author **07640419**
 * \author **ee_cmx**
 * \author **LA1A**
 *
 * \date **2009.5.3**
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2009.05.17 at 23:00 by CASS
 * 
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <stdexcept>
#include <map>
#include <list>

using namespace std;



/**
 * \class Cell
 * \brief Class Cell:The abstract base class
 */
class Cell {
private:

public:
	/**
        * \brief The Constructor of the abstract base class.
        * 
        */
  	Cell(){};

  	//virtual ~Cell()=0;
        /**
	* \brief Accessor (error if this is not an IntCell).
	* \return The value in this int cell.
	*/
  	virtual int get_int() const{throw runtime_error("This is not an IntCell");}

  	/**
	* \brief Accessor (error if this is not a DoubleCell).
	* \return The value in this double cell.
	*/
  	virtual double get_double() const{throw runtime_error("This is not a DoubleCell");}

  	/**
	* \brief Accessor (error if this is not a SymbolCell).
	* \return The value in this symbol cell.
	*/
  	virtual string get_symbol() const{return "Invalid symbol";}

  	/**
	* \brief Accessor (error if this is not a ConsCell).
	* \return The car in this ConsCell.
	*/
  	virtual Cell* get_car() const{throw runtime_error("This is not a ConsCell");}

  	/**
	* \brief Accessor (error if this is not a ConsCell).
	* \return The cdr in this ConsCell.
	*/
  	virtual Cell* get_cdr() const{throw runtime_error("This is not a ConsCell");}
  	//////////
  	

  	/**
	* \brief Check if this is an IntCell.
	* \return True iff this is an IntCell.
	*/
  	virtual bool is_int() const{return false;}

  	/**
	* \brief Check if this is an DoubleCell.
	* \return True iff this is an DoubleCell.
	*/
  	virtual bool is_double() const{return false;}

  	/**
	* \brief Check if this is an SymbolCell.
	* \return True iff this is an SymbolCell.
	*/
  	virtual bool is_symbol() const{return false;}

  	/**
	* \brief Check if this is an ConsCell.
	* \return True iff this is an ConsCell.
	*/
  	virtual bool is_cons() const{return false;}

  	/**
	* \brief A pure virtual function. Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
  	virtual void print(ostream& os = cout) const=0;

  	/**
	* \brief Executue ceiling operation.
	* \return The result of ceiling 
	*/
	virtual int ceiling_operation(){throw runtime_error("Invalid input type for CEILING");}

	/**
	* \brief Executue floor operation.
	* \return The result of floor 
	*/
	virtual int floor_operation(){throw runtime_error("Invalid input type for FLOOR");}

	/**
	* \brief Check if the object is zero.
	* \return False if zero, true if non-zero
	*/
	virtual bool if_operation(){};//return false if 0, return true if non-zero

	/**
	* \brief Check if the object is valid as an operand for the four operation: + - * /.
	* \return True if it's valid .Exit the program if it is invalid
	*/
	virtual bool valid_type_four(){throw runtime_error("Invalid operand type");}

	/**
	* \brief Execute addition between two objects of Cell.
	* \param addened The input to be added with the object
	* \return A pointer to the additon result
	*/
	virtual Cell* addition(Cell* addened) {throw logic_error("Invalid input type for ADD");}

	/**
	* \brief Execute multiplication between two objects of Cell.
	* \param multed The input to be multiplied with the object
	* \return A pointer to the multiplication result
	*/
	virtual Cell* multiplication(Cell* multed) {throw logic_error("Invalid input type for SUB");}

	/**
	* \brief Execute subtraction between two objects of Cell.
	* \param sub The input subtracting the object
	* \return A pointer to the subtraction result
	*/
	virtual Cell* subtraction(Cell* sub) {throw logic_error("Invalid input type for MULT");}

	/**
	* \brief Execute division between two objects of Cell.
	* \param div The input dividing the object
	* \return A pointer to the division result
	*/
	virtual Cell* division(Cell* div) {throw logic_error("Invalid input type for DIV");}
	
	/**
	* \brief Check if the object is smaller than the parameter
	* \param operand The object to be compared
	* \return True if it's smaller .
	*/
        virtual bool smaller(Cell* operand){throw runtime_error("Invalid operand type for <");}
        
        /**
	* \brief Check if the object is an operator.
	* \return True if it's an operator .
	*/
        virtual bool is_operator(){return false;}
        /**
	* \brief Check if the object is a built-in-procedure
	* \return True if it's a built-in-procedure .
	*/
        virtual bool procedure_built_in(){return false;}
        /**
	* \brief Accessor (error if this is not a ProcedureCell).
	* \return The formals in this ProcedureCell.
	*/
        virtual Cell* get_formals() const{throw logic_error("This is not a ProcedureCell");}
        /**
	* \brief Accessor (error if this is not a ProcedureCell).
	* \return The body in this ProcedureCell.
	*/
  	virtual Cell* get_body() const{throw logic_error("This is not a ProcedureCell");}
  	/**
	* \brief Check if this is an ProcedureCell.
	* \return True iff this is an ProcedureCell.
	*/
  	virtual bool is_procedure() const{return false;}
  	/**
	* \brief Apply the procedure to a list
	* \param args The input arguments.
	*/
  	virtual Cell* apply(Cell* args){throw runtime_error("This is not a ProcedureCell");};
};



/**
 * \class IntCell
 * \brief Class IntCell:The abstract base class
 */
class IntCell: public Cell{
private:
  	int int_m;
public:
	/**
        * \brief The Constructor of the IntCell.
        * \param i The input int to initialize the IntCell.
        */
  	IntCell(int i);

  	//~IntCell();
  	/**
	* \brief Accessor (error if this is not an IntCell).
	* \return The value in this int cell.
	*/
  	int get_int() const;

  	/**
	* \brief Check if this is an IntCell.
	* \return True .
	*/
  	bool is_int() const;

  	/**
	* \brief Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
  	void print(ostream& os = cout) const;

  	/**
	* \brief Check if the object is zero.
	* \return False if zero, true if non-zero
	*/
  	bool if_operation();

  	/**
	* \brief Check if the object is valid as an operand for the four operation: + - * /.
	* \return True
	*/
  	bool valid_type_four();

  	/**
	* \brief Execute addition between an IntCell and the input Cell.
	* \param addened The input to be added with the object
	* \return A pointer to the additon result
	*/
  	Cell* addition(Cell* addened);

  	/**
	* \brief Execute multiplication between an IntCell and the input Cell.
	* \param multed The input to be multiplied with the object
	* \return A pointer to the multiplication result
	*/
  	Cell* multiplication(Cell* multed);

  	/**
	* \brief Execute subtraction between an IntCell and the input Cell.
	* \param sub The input subtracting the object
	* \return A pointer to the subtraction result
	*/
  	Cell* subtraction(Cell* sub);

  	/**
	* \brief Execute division between an IntCell and the input Cell. 0 can't be a divider.
	* \param div The input dividing the object
	* \return A pointer to the division result
	*/
  	Cell* division(Cell* div);
  	
  	/**
	* \brief Check if the object is smaller than the parameter
	* \param operand The object to be compared
	* \return True if it's smaller .
	*/
  	bool smaller(Cell* operand);

};



/**
 * \class DoubleCell
 * \brief Class DoubleCell:The abstract base class
 */
class DoubleCell: public Cell {
private:
  	double double_m;
public:
	/**
        * \brief The Constructor of the DoubleCell.
        * \param d The input int to initialize the DoubleCell.
        */
  	DoubleCell(double d);

  	//~DoubleCell();
  	/**
	* \brief Accessor (error if this is not a DoubleCell).
	* \return The value in this double cell.
	*/
  	double get_double() const;

  	/**
	* \brief Check if this is an DoubleCell.
	* \return True 
	*/
  	bool is_double() const;

  	/**
	* \brief Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
  	void print(ostream& os = cout) const;

  	/**
	* \brief Executue ceiling operation.
	* \return The result of ceiling 
	*/
	int ceiling_operation();

	/**
	* \brief Executue floor operation.
	* \return The result of floor 
	*/
	int floor_operation();

	/**
	* \brief Check if the object is zero.
	* \return False if zero, true if non-zero
	*/
	bool if_operation();

	/**
	* \brief Check if the object is valid as an operand for the four operation: + - * /.
	* \return True
	*/
	bool valid_type_four();

	/**
	* \brief Execute addition between two objects of Cell.
	* \param addened The input to be added with the object
	* \return A pointer to the additon result
	*/
	Cell* addition(Cell* addened);

	/**
	* \brief Execute multiplication between a DoubleCell and the input Cell.
	* \param multed The input to be multiplied with the object
	* \return A pointer to the multiplication result
	*/
	Cell* multiplication(Cell* multed);

	/**
	* \brief Execute subtraction between a DoubleCell and the input Cell.
	* \param sub The input subtracting the object
	* \return A pointer to the subtraction result
	*/
	Cell* subtraction(Cell* sub);

	/**
	* \brief Execute division between a DoubleCell and the input Cell. 0 can't be a divider.
	* \param div The input dividing the object
	* \return A pointer to the division result
	*/
	Cell* division(Cell* div);
	/**
	* \brief Check if the object is smaller than the parameter
	* \param operand The object to be compared
	* \return True if it's smaller .
	*/
	bool smaller(Cell* operand);
};



/**
 * \class SymbolCell
 * \brief Class SymbolCell:The abstract base class
 */
class SymbolCell: public Cell {
private:
  	char* symbol_m;
public:
	/**
   	* \brief Constructor to make symbol cell.
   	* \param s The input symbol to initialize the cell.
   	*/
  	SymbolCell(const char* const s);

  	//~SymbolCell();
  	/**
	* \brief Accessor (error if this is not a SymbolCell).
	* \return The value in this symbol cell.
	*/
  	string get_symbol() const;

  	/**
	* \brief Check if this is an SymbolCell.
	* \return True
	*/
  	bool is_symbol() const;

  	/**
	* \brief Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
  	void print(ostream& os = cout) const;

  	/**
	* \brief Check if the object is zero.
	* \return True
	*/
  	bool if_operation();
  	
  	/**
	* \brief Check if the object is an operator.
	* \return True if it's an operator .
	*/
  	bool is_operator();
  	bool procedure_built_in();
  	/**
	* \brief Check if the object is smaller than the parameter
	* \param operand The object to be compared
	* \return True if it's smaller .
	*/
	bool smaller(Cell* operand);
  	
};



/**
 * \class ConsCell
 * \brief Class ConsCell:The abstract base class
 */
class ConsCell: public Cell {
private:
  	Cell* car;
  	Cell* cdr;
public:
	/**
   	* \brief Constructor to make ConsCell.
   	* \param my_car The input left child to initialize the cell.
   	* \param my_cdr The input left child to initialize the cell.
   	*/
  	ConsCell(Cell* const my_car, Cell* const my_cdr);

  	//~ConsCell();
  	/**
	* \brief Accessor (error if this is not a ConsCell).
	* \return The car in this ConsCell.
	*/
  	Cell* get_car() const;

  	/**
	* \brief Accessor (error if this is not a ConsCell).
	* \return The cdr in this ConsCell.
	*/
  	Cell* get_cdr() const;

  	/**
	* \brief Check if this is an ConsCell.
	* \return True iff this is an ConsCell.
	*/
  	bool is_cons() const;

  	/**
	* \brief Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
  	void print(ostream& os = cout) const;
  	/**
	* \brief Check if the object is zero.
	* \return True
	*/
  	bool if_operation();
  	
  	
};

// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;
/**
 * \class ProcedureCell
 * \brief Class ProcedureCell:The abstract base class
 */
class ProcedureCell: public Cell{
private:
	 Cell* formals;
	 Cell* body;
public:
        /**
   	* \brief Constructor to make ConsCell.
   	* \param my_formals The input formal to initialize the cell.
   	* \param my_body The input body to initialize the cell.
   	*/
	ProcedureCell(Cell* const my_formals,Cell* const my_body);
	/**
	* \brief Accessor (error if this is not a ProcedureCell).
	* \return The formals in this ProcedureCell.
	*/
	Cell* get_formals() const;
	/**
	* \brief Accessor (error if this is not a ProcedureCell).
	* \return The body in this ProcedureCell.
	*/
	Cell* get_body() const;
	/**
	* \brief Check if this is an ProcedureCell.
	* \return True iff this is an ProcedureCell.
	*/
	bool is_procedure() const;
	/**
	* \brief Print the subtree rooted at this cell, in s-expression notation.
	* \param os The output stream to print to.
	*/
	void print(ostream& os = cout) const;
	/**
	* \brief Check if the object is zero.
	* \return True
	*/
	bool if_operation();
	/**
	* \brief Apply the procedure to a list
	* \param args The input arguments.
	*/
	Cell* apply(Cell* args);
	
};

extern map<string,Cell*> symbol_table;
extern list< map<string,Cell*> > map_list;

int operand_num(Cell*c);
#endif // CELL_HPP

