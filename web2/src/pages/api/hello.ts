// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import { exec, execSync } from "child_process";
import type { NextApiRequest, NextApiResponse } from "next";

export default function handler(
  req: NextApiRequest,
  res: NextApiResponse,
) {
  const result = execSync("./lox" )
  res.status(200).json({ result: result.toString() });
}
