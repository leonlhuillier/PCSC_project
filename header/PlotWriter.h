#ifndef PLOTWRITER_H
#define PLOTWRITER_H

#include <string>

#include "Writer.h"

/**
 * \class PlotWriter
 * \brief Implements the Writer interface to generate and save graphical plots of the solution process and results.
 *
 * \details The PlotWriter is a concrete strategy for outputting results visually. It is typically used
 * to generate plots of the convergence history (e.g., eigenvalue error vs. iteration count) or to
 * visualize key characteristics of the eigenvector. It saves the resulting graph to a specified file,
 * usually requiring an external plotting library (like gnuplot or matplotlib-cpp) in the underlying
 * implementation of \c Write().
 *
 * \ingroup Writer
 * \sa Writer
 */
class PlotWriter : public Writer {
public:
    // Constructors and Destructors
    /**
     * \brief Constructs a PlotWriter object, setting the output file path for the plot image.
     * \param filename The path and name (including extension, e.g., "convergence.png") where the plot should be saved.
     */
    PlotWriter(const std::string & filename);

    /**
     * \brief Destructor for PlotWriter.
     */
    virtual ~PlotWriter();

    // Public virtual Method
    /**
     * \brief Generates the plot using the computed data and saves it to the configured file.
     *
     * \details This overridden method collects the necessary data (e.g., iteration data collected
     * during the solver's execution), constructs the plot (e.g., a line graph showing error reduction),
     * and saves the resulting image to \c mFilename.
     * \pre The solver process must have successfully completed, and relevant iteration history must be available.
     * \post A graphical file (e.g., PNG, SVG) is created at the location specified by \c mFilename.
     *
     */
    virtual void Write() override;

private:
    /**
     * \brief The file path where the generated plot will be saved.
     */
    std::string mFilename;
};

#endif //PLOTWRITER_H