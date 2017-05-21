var cp = require('child_process');
var fs = require('fs');

var tasks = [{
    name: "init",
    cpu: 0.1,
    mem: 1,
    time: 200000
}, {
    name: "a",
    cpu: 0.1,
    mem: 10,
    time: 20000
}, {
    name: "b",
    cpu: 0.1,
    mem: 10,
    time: 20000
}, {
    name: "c",
    cpu: 0.1,
    mem: 10,
    time: 20000
}];
process.stdin.setEncoding('utf8');

process.stdin.on('readable', () => {
    var chunk = process.stdin.read();
    if (chunk !== null) {
        // process.stdout.write(chunk);
        let temp = chunk.split(' ');
        if (temp.length == 3) {
            console.log(`${temp[0]}:${temp[1]}\t${temp[2]}`);
            tasks.push({
                name: temp[0],
                cpu: Number(temp[1]),
                mem: Number(temp[2]),
                time: 40000
            })
        }
    }
});

process.stdin.on('end', () => {
    process.stdout.write('end');
});

function timeout(ms) {
    return new Promise(function (resolve, reject) {
        setTimeout(resolve, ms);
    })
}

var CPU = 1.5; // percentage
var Mem = 50; // MB

async function main() {
    var runqueue = [];
    var task;
    var slice = 1000;
    var total = 0;
    console.log('OS running...');
    while (true) {
        if (tasks[0]) {
            task = tasks[0];    
            if (CPU > getCpu() + task.cpu && Mem < getMem() - task.mem) {
                var object = {
                    object: task,
                    remains: slice,
                    pid: 0
                }
                var child = cp.execFile('./load', [task.cpu.toString(), task.mem.toString()]);
                object.pid = child.pid;
                runqueue.push(object);
                tasks.shift();
                console.log(cp.execSync('clear').toString());
                total = 0;
                var len = runqueue.length;
                for (var i = 0; i < len; i++) {
                    task = runqueue[i];
                    console.log(`Running task: ${task.object.name}`);
                }
                console.log(`the ratio of CPU is ${getCpu()}`);
                console.log(`the ratio of Mem is ${getMem()}`);
            }
        }
        var len = runqueue.length;
        for (var i = 0; i < len; i++) {
            task = runqueue.shift();
            task.remains -= 100;
            if (task.remains <= 0) {
                task.object.time -= slice;
                if (task.object.time > 0) {
                    tasks.push(task.object);
                }
                // console.log(task.object.time);
                process.kill(task.pid, "SIGTERM");
                console.log(cp.execSync('clear').toString());
                total = 0;
                var len = runqueue.length;
                for (var i = 0; i < len; i++) {
                    task = runqueue[i];
                    console.log(`Running task: ${task.object.name}`);
                }
                console.log(`the ratio of CPU is ${getCpu()}`);
                console.log(`the ratio of Mem is ${getMem()}`);
            } else {
                runqueue.push(task);
            }
        }

        if (total % 5000 == 0) {
            console.log(cp.execSync('clear').toString());
            total = 0;
            var len = runqueue.length;
            for (var i = 0; i < len; i++) {
                task = runqueue[i];
                console.log(`Running task: ${task.object.name}`);
            }
            console.log(`the ratio of CPU is ${getCpu()}`);
            console.log(`the ratio of Mem is ${getMem()}`);
        }
        await timeout(500);
        total += 500;
    }
}

function getMem() {
    var result = cp.execSync("free -m");
    result = result.toString();
    result = result.split(' ');
    result = result.filter(function (e) {
        if (e == '') return false;
        else return true;
    })
    result = result[11].split('\n');
    return Number(result[0]);
}

function getCpu() {
    var result = fs.readFileSync('/proc/loadavg');
    result = result.toString();
    result = result.split(' ');
    return Number(result[0]);
}


main();