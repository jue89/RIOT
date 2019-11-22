const fs = require('fs');

const msg = fs.readFileSync('./leo.txt').toString();

msg.replace(/\\/g, '\\\\').replace(/"/g, '\\"').split('\n').forEach((line) => {
	console.log(`    "${line}\\n" + \\`);
});
