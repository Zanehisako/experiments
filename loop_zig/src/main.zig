const std = @import("std");
const net = std.net;
const posix = std.posix;

pub fn main() !void {
    const address = try std.net.Address.parseIp("127.0.0.1", 5882);

    std.debug.print("Started the server at address :127.0.0.1 port 5882\n", .{});
    const tpe: u32 = posix.SOCK.STREAM;
    const protocol = posix.IPPROTO.TCP;
    const listener = try posix.socket(address.any.family, tpe, protocol);
    defer posix.close(listener);

    try posix.setsockopt(listener, posix.SOL.SOCKET, posix.SO.REUSEADDR, &std.mem.toBytes(@as(c_int, 1)));
    try posix.bind(listener, &address.any, address.getOsSockLen());
    try posix.listen(listener, 128);

    var buf: [128]u8 = undefined;
    while (true) {
        var client_address: net.Address = undefined;
        var client_address_len: posix.socklen_t = @sizeOf(net.Address);
        const socket = posix.accept(listener, &client_address.any, &client_address_len, 0) catch |err| {
            // Rare that this happens, but in later parts we'll
            // see examples where it does.
            std.debug.print("error accept: {}\n", .{err});
            continue;
        };
        defer posix.close(socket);

        std.debug.print("{} connected\n", .{client_address});

        const timeout = posix.timeval{ .tv_sec = 2, .tv_usec = 500_000 };
        posix.setsockopt(socket, posix.SOL.SOCKET, posix.SO.RCVTIMEO, &std.mem.toBytes(timeout)) catch |err| {
            std.debug.print("error:{any} occured when setting the socket options\n", .{err});
        };
        posix.setsockopt(socket, posix.SOL.SOCKET, posix.SO.SNDTIMEO, &std.mem.toBytes(timeout)) catch |err| {
            std.debug.print("error:{any} occured when setting the socket options\n", .{err});
        };

        // we've changed everything from this point on
        const stream = std.net.Stream{ .handle = socket };

        var read: usize = undefined;
        while (true) {
            read = stream.read(&buf) catch |err| {
                if (err == error.WouldBlock) {
                    std.debug.print("waiting for user input \n", .{});
                    continue;
                } else {
                    std.debug.print("{any} occured when traying to write to the stream\n", .{err});
                    return err;
                }
            };
            std.debug.print("reading successfully", .{});
            break;
        }
        const hello = " hello";
        @memcpy(buf[read - 1 ..], hello);
        stream.writeAll(&buf) catch |err| {
            std.debug.print("{any} occured when trying to write to the stream", .{err});
        };
    }
}
