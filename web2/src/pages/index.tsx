import EditorComponent from "@/components/EditorComponent";
import TreeComponent from "@/components/TreeComponent";

export default function Home() {
  return (
    <>
	<h1 className="text-4xl font-bold text-center">Visualizer</h1>
      <div className={`flex min-h-screen justify-between p-24`}>
        <div className="w-1/2 shadow shadow-black m-2">
		<h2 className="text-2xl font-bold text-center">Editor</h2>
          <EditorComponent />
        </div>
        <div className="w-1/2 shadow shadow-black m-2">
		<h2 className="text-2xl font-bold text-center">Parse Tree</h2>
          <TreeComponent />
        </div>
      </div>
    </>
  );
}
