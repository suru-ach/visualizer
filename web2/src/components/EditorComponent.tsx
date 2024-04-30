import { useState } from "react";
import Editor from "react-simple-code-editor";
import { highlight, languages } from 'prismjs/components/prism-core';
import 'prismjs/components/prism-clike';
import 'prismjs/components/prism-javascript';
import 'prismjs/themes/prism.css'; //Example style, you can use another

export default function EditorComponent() {
  const [code, setCode] = useState(
    `function add(a, b) {\n  return a + b;\n}`
  );

  function doSomething(code: string)
 {
		setCode(code);
		localStorage.setItem('code', code);
  }
return (
<Editor
      value={code}
      onValueChange={code => doSomething(code)}
      highlight={code => highlight(code, languages.js)}
      padding={10}
      style={{
        fontFamily: '"Fira code", "Fira Mono", monospace',
        fontSize: 16,
      }}
    />
);
}
