import dynamic from "next/dynamic";
import { useEffect, useState } from "react";
import { RawNodeDatum } from "react-d3-tree";
const Tree = dynamic(() => import("react-d3-tree"), { ssr: false });

export default function TreeComponent({data}: {data: RawNodeDatum}) {
  return (
    <div
      id="treeWrapper"
      className={"flex items-center"}
      style={{ width: "100%", height: "100%" }}
    >
      <Tree
        orientation="vertical"
        dimensions={{ width: 1000, height: 10000 }}
        zoom={0.5}
        data={data || {}}
      />
    </div>
  );
}
