// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import { exec, execSync } from "child_process";
import { readFileSync, writeFileSync } from "fs";
import type { NextApiRequest, NextApiResponse } from "next";

export default function handler(
  req: NextApiRequest,
  res: NextApiResponse,
) {
	try {
  const code = req.body;
  console.log(code);
  writeFileSync("test.txt", code);
  execSync("./lox test.txt > out.json" )
  const data = readFileSync("out.json", "utf-8");
  res.status(200).json({ result: data});
	}
	catch (e) {
		console.log(e);
		res.status(200).json({ error: "An error occurred"});
	}
}
