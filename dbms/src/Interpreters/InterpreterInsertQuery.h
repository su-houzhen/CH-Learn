#pragma once

#include <DataStreams/IBlockOutputStream.h>
#include <DataStreams/BlockIO.h>
#include <Interpreters/Context.h>
#include <Interpreters/IInterpreter.h>


namespace DB
{


/** Interprets the INSERT query.
  */
class InterpreterInsertQuery : public IInterpreter
{
public:
    InterpreterInsertQuery(const ASTPtr & query_ptr_, const Context & context_);

    /** Prepare a request for execution. Return block streams
      * - the stream into which you can write data to execute the query, if INSERT;
      * - the stream from which you can read the result of the query, if SELECT and similar;
      * Or nothing if the request INSERT SELECT (self-sufficient query - does not accept the input data, does not return the result).
      */
    BlockIO execute() override;

private:
    StoragePtr getTable();

    Block getSampleBlock();

    ASTPtr query_ptr;
    const Context & context;
};


}