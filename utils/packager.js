"use strict"

// packager tool for the SageEasyC library
// run it with Deno

// expecting the file "source/safe-easy-c-source.h" to not have
// #preprocessor-include-directives with unnecessary whitespaces 

var consolidation = ""

// main ///////////////////////////////////////////////////////////////////////

function main() { 
 // console.log("\u001Bc") // *clears console perfectly* //
    console.log("packaging SafeEasyC")
    processOptions()
    mount()
    Deno.writeTextFileSync("safe-easy-c.h", consolidation)
}

// options ////////////////////////////////////////////////////////////////////

function processOptions() {
    //
    const option = Deno.args.slice(0, Deno.args.length).shift()
    //
    if (option == undefined) { return }
    //
    console.log("ERROR: unknown option:", option)
    Deno.exit(1)    
}

// mount //////////////////////////////////////////////////////////////////////

function mount() {
    applyHead()
    applyBody()
    applyFoot()
}

function applyHead() {
    consolidation  = "" +
 // "// # Copyright (c) 2014-2024 Feudal Code Limitada #\n\n" + // copyright is provided by the source file
    "///////////////////////////////////////////////////////////////////////////////\n" +
    "///                            SafeEasyC Library                            ///\n" +
    "///                                                                         ///\n" +
    "///                    DO   **NOT**   EDIT   THIS   FILE!                   ///\n" +
    "///                                                                         ///\n" +
    "///                https://github.com/JoanaBLate/safe-easy-c                ///\n" +
    "///////////////////////////////////////////////////////////////////////////////\n\n"
}

function applyBody() {
    //
    const sourceLines = loadLines("source/safe-easy-c-source.h")
    //
    for (const line of sourceLines) { 
        //
        if (line.startsWith('#include "')) { consolidateLinkedFile(line); continue }
        //
        consolidation += line + "\n"
    }
} 

function applyFoot() {
    consolidation += "\n"
}

///////////////////////////////////////////////////////////////////////////////

function consolidateLinkedFile(trim) {
    //
    const path = trim.replace('#include "', "").replace('"', "")
    //
    let txt = "\n\n// file: " + path + " //\n"
    //
    const lines = loadLines("source/" + path)
    lines.shift() // copyright
    for (const line of lines) { txt += line + "\n" }
    consolidation += txt
}

///////////////////////////////////////////////////////////////////////////////

function loadLines(path) {
    const text = loadFile(path).trimRight()
    const lines = text.split("\n")    
    for (let n = 0; n < lines.length; n++) {
        lines[n] = lines[n].trimRight()
    }
    return lines
}

function loadFile(path) {
    try {
        return Deno.readTextFileSync(path)
    }
    catch (__e) {
        console.log("ERROR: could not read: " + path) 
        Deno.exit(1)       
    }
}

// boot ///////////////////////////////////////////////////////////////////////

main()

