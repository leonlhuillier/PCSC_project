#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

#include <string>

#include "Writer.h"

/**
 *\class ConsoleWriter
 * \brief Implements the Writer interface to output computation results directly to the console.
 *
 * \details The ConsoleWriter output the results, such as the eigenvalues and eigenvector
 * onto the console. The user can see it directly.
 */
class ConsoleWriter : public Writer {
public:
    /**
     * \brief Default constructor for ConsoleWriter.
     */
    ConsoleWriter();
    /**
     * \brief Default destructor for ConsoleWriter.
     */
    virtual ~ConsoleWriter();
    /**
     * \brief Writes the final results of the eigenvalue calculation to the console.
     *
     * \details This overridden method formats and prints the eigenvalue
     * and the associated eigenvector (eigenvector) using `std::cout`.
     * \pre The solver process must have successfully converged and calculated the results.
     */
    virtual void Write() override;

};

#endif //CONSOLEWRITER_H