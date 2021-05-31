struct file_operations fops=
{
	open:opendev,
	release:releasedev,
	read:readdev,
	write:writedev,
	llseek:llseekdev,
};
