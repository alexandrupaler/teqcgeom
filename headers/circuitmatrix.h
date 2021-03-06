#ifndef CIRCUITMATRIX_H_
#define CIRCUITMATRIX_H_

#include <vector>
#include <set>
#include "fileformats/generaldefines.h"

/**
 * Representation of a quantum circuit as a matrix of integer values.
 */
class circuitmatrix {
public:
	circuitmatrix();
	circuitmatrix(std::vector<qubitline> orig);

	/**
	 * Checks if at a given matrix coordinate the value represents an input.
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if input, false otherwise
	 */
	bool isInput(int i, int j);

	/**
	 * Checks if at a given matrix coordinate the value represents an output.
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if output, false otherwise
	 */
	bool isOutput(int i, int j);

	/**
	 * Checks if at a given matrix coordinate the inputs are distillable injections
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if output, false otherwise
	 */
	bool isDistillationAncillaInput(int i, int j);

	/**
	 * Checks if at a given matrix coordinate the value represents an empty wire (no gate).
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if no gate, false otherwise
	 */
	bool isWire(int i, int j);

	/**
	 * Checks if at a given matrix coordinate no qubit exists.
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if no qubit, false otherwise
	 */
	bool isEmpty(int i, int j);

	/**
	 * Checks if at a given matrix coordinate the value represents a qubit initialisation basis.
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if initialisation, false otherwise
	 */
	bool isInitialisation(int i, int j);

	/**
	 * Checks if at a given matrix coordinate the value represents a qubit measurement basis.
	 * @param i matrix line (qubit)
	 * @param j matrix columns (gate)
	 * @return true if measurement, false otherwise
	 */
	bool isMeasurement(int i, int j);

	/**
	 * Checks if the specified index is less than the length of the qubit's wire.
	 * @param i matrix line (qubit)
	 * @param index possible
	 * @return true if length is longer, false otherwise
	 */
	bool indexLessThanSize(size_t i, size_t index);

	/**
	 * Returns a Boolean value indicating if the circuit uses injected states.
	 * @return true if there exist qubits with injections, false otherwise
	 */
	bool hasInjections();

	/**
	 * Searches in the circuit for the targets of a given CNOT specified by the coordinates of the control
	 * @param i the line of the control
	 * @param j the column of the control
	 * @return vector of lines where control are founds (multiple control CNOTs are possible)
	 */
	std::vector<int> findTarget(int i, int j);

	/**
	 * Searches in the circuit for the controls of a given CNOT specified by the coordinates of the target
	 * @param i the line of the target
	 * @param j the column of the target
	 * @return vector of lines where targets are founds (multiple target CNOTs are possible)
	 */
	std::vector<int> findControl(int i, int j);

	/**
	 *
	 * @return The maximum length of a qubit line in the circuit.
	 */
	size_t getMaxColumn();

	/**
	 *
	 * @return number of circuit qubits
	 */
	int getNrLines();

	/**
	 * For debugging purposes
	 */
	void printCirc();

	/**
	 * Deletes all the columns consisting entirely of wires or empty.
	 */
	void removeEmptyColumns();

	/**
	 * Deletes all the lines (qubits) which are not used: never initialised, measured etc.
	 */
	void removeEmptyRows();

	/**
	 * Inserts additional lines (qubits) into the matrix representation.
	 * @param beforePosition index of the line before which lines are introduced
	 * @param rows a vector of qubits to be introduced
	 */
	void insertRows(int beforePosition, std::vector<qubitline>& rows);

	/**
	 * Inserts additional columns (empty cells representing no gates) on each circuit line
	 * @param beforePosition index of the column before which columns are introduced
	 * @param nrColumns number of columns to introduce
	 */
	void insertColumns(int beforePosition, int nrColumns);

	qubitline& operator[](int i);
	qubitline& at(int i);

	/**
	 * Equivalent to getNrLines()
	 * @return
	 */
	size_t size(){return circ.size();};

	/**
	 * Checks if on a column there already exists a cnot
	 */
	bool checkForCnotOnColumn(int column);

private:
	/**
	 * The circuit represented as a vector of lines, where each qubitline is a vector of integers.
	 */
	std::vector<qubitline> circ;

	/**
	 * Method used for initialising class members.
	 */
	void init();
};


#endif /* CIRCUITMATRIX_H_ */
