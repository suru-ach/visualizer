import EditorComponent from "@/components/EditorComponent";
import TreeComponent from "@/components/TreeComponent";
import { useEffect, useState } from "react";

export default function Home() {
  const [code, setCode] = useState<string>("");
  const [error, setError] = useState<string>("");
  const [tree, setTree] = useState("");
  async function fetchData() {
    try {
      const res = await fetch("/api/compile", {
        method: "POST",
        body: code,
      });
      const data = await res.json();
      if (data.error) return setError(data.error);
      if (data.result.startsWith("{")) setTree(data.result);
    } catch (error) {
      console.error(error);
    }
  }

  return (
    <>
      <h1 className="text-4xl font-bold text-center">Visualizer</h1>
      <div className={`flex min-h-screen justify-between p-24`}>
        <div className="w-1/2 shadow shadow-black m-2">
          <h2 className="text-2xl font-bold text-center">Editor</h2>
          <button onClick={fetchData} className="p-2 float-right mx-2 bg-blue-400 rounded">
            Parse
          </button>
          <EditorComponent setCode={setCode} code={code} />
        </div>
        <div className="w-1/2 shadow shadow-black m-2">
          <h2 className="text-2xl font-bold text-center">Parse Tree</h2>
          <TreeComponent data={tree ? JSON.parse(tree) : {}} />
        </div>
      </div>
    </>
  );
}
