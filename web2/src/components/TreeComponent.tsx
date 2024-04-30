import dynamic from "next/dynamic";
const Tree = dynamic(() => import("react-d3-tree"), { ssr: false });

const orgChart = JSON.parse('{}');

/*
const orgChart = {
  name: "CEO",
  children: [
    {
      name: "Manager",
      attributes: {
        department: "Production",
      },
      children: [
        {
          name: "Foreman",
          attributes: {
            department: "Fabrication",
          },
          children: [
            {
              name: "Worker",
            },
          ],
        },
        {
          name: "Foreman",
          attributes: {
            department: "Assembly",
          },
          children: [
            {
              name: "Worker",
            },
          ],
        },
      ],
    },
  ],
};
*/

export default function TreeComponent() {
  return (
    <div id="treeWrapper" className={"flex items-center"} style={{ width: "100%", height: "100%" }}>
      <Tree 
	  orientation="vertical"
	  dimensions={{ width: 1000, height: 10000 }}
	  zoom={0.5}
	  data={orgChart} />
    </div>
  );
}
